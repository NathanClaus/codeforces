#!/usr/bin/env python3
import re
import os
import sys
import argparse
from collections import defaultdict

def get_function_definitions(library_content):
    """
    Extract function and class definitions from the library file.
    Returns a dictionary of entity name -> full definition (including dependencies).
    """
    # Pattern for function/method signatures
    function_pattern = re.compile(r'(template\s*<.*?>\s*)?(inline\s*)?(.*?\s+)?(\w+)\s*\([^)]*\)\s*{', re.DOTALL)
    
    # Pattern for class/struct definitions
    class_pattern = re.compile(r'(struct|class)\s+(\w+)\s*{', re.DOTALL)
    
    # Pattern for namespace definitions
    namespace_pattern = re.compile(r'namespace\s+(\w+)\s*{', re.DOTALL)
    
    # Find all function definitions
    entities = {}
    lines = library_content.split('\n')
    
    # Process the file line by line
    i = 0
    while i < len(lines):
        line = lines[i]
        
        # Check for namespace
        namespace_match = namespace_pattern.search(line)
        if namespace_match:
            namespace_name = namespace_match.group(1)
            start_line = i
            brace_count = line.count('{') - line.count('}')
            
            # Find the end of the namespace
            j = i + 1
            while j < len(lines) and brace_count > 0:
                brace_count += lines[j].count('{') - lines[j].count('}')
                j += 1
            
            # Extract the entire namespace
            namespace_content = '\n'.join(lines[start_line:j])
            entities[namespace_name] = namespace_content
            i = j
            continue
        
        # Check for class/struct definitions
        class_match = class_pattern.search(line)
        if class_match:
            class_name = class_match.group(2)
            start_line = i
            brace_count = line.count('{') - line.count('}')
            
            # Find the end of the class/struct
            j = i + 1
            while j < len(lines) and brace_count > 0:
                brace_count += lines[j].count('{') - lines[j].count('}')
                j += 1
            
            # Extract the entire class/struct definition
            class_content = '\n'.join(lines[start_line:j])
            entities[class_name] = class_content
            
            # Also extract the ostream operator<< for this class if it exists
            for k in range(j, min(j + 20, len(lines))):  # Look ahead a few lines
                if f"ostream& operator<<(ostream& os, const {class_name}" in lines[k]:
                    op_start = k
                    op_brace_count = lines[k].count('{') - lines[k].count('}')
                    
                    # Find the end of the operator function
                    l = k + 1
                    while l < len(lines) and op_brace_count > 0:
                        op_brace_count += lines[l].count('{') - lines[l].count('}')
                        l += 1
                    
                    # Add operator<< to entities
                    op_name = f"operator<<_{class_name}"
                    entities[op_name] = '\n'.join(lines[op_start:l])
                    break
            
            i = j
            continue
        
        # Check for function definitions
        func_match = function_pattern.search(line)
        if func_match:
            # Extract the function name and signature
            func_name = func_match.group(4)
            start_line = i
            
            # Count opening and closing braces to find the end of the function
            brace_count = line.count('{') - line.count('}')
            
            # Find the end of the function
            j = i + 1
            while j < len(lines) and brace_count > 0:
                brace_count += lines[j].count('{') - lines[j].count('}')
                j += 1
            
            # Extract the entire function definition
            func_content = '\n'.join(lines[start_line:j])
            entities[func_name] = func_content
            i = j
            continue
        
        i += 1
    
    return entities

def find_dependencies(solution_content, library_entities):
    """
    Find which library entities are used in the solution file.
    Returns a list of entity names that need to be included.
    """
    required_entities = set()
    
    # Check for each entity
    for entity_name, _ in library_entities.items():
        # For namespaces, we check if they're used with scope resolution operator
        if entity_name in ["Geometry", "Maps"]:
            if f"{entity_name}::" in solution_content:
                required_entities.add(entity_name)
        # For Point2D and Point3D classes which might be used without namespace
        elif entity_name in ["Point2D", "Point3D"]:
            pattern = rf'\b{entity_name}\b'
            if re.search(pattern, solution_content):
                required_entities.add(entity_name)
                # If we're using a Point class, we might need the Geometry namespace too
                required_entities.add("Geometry")
        # For regular functions and classes
        else:
            pattern = rf'\b{entity_name}\b'
            if re.search(pattern, solution_content):
                required_entities.add(entity_name)
    
    # Expand dependencies (e.g., if a function uses a class)
    expanded_entities = required_entities.copy()
    
    # Check for dependencies between entities
    # This is a simple approach - might need enhancement for complex dependency structures
    for entity_name in required_entities:
        entity_content = library_entities[entity_name]
        for other_entity in library_entities:
            if other_entity != entity_name and other_entity in entity_content:
                expanded_entities.add(other_entity)
    
    return expanded_entities

def build_dependency_graph(entities, library_entities):
    """
    Build a directed graph of dependencies between entities.
    Returns a dictionary where keys are entities and values are sets of entities they depend on.
    """
    dependency_graph = defaultdict(set)
    
    for entity in entities:
        entity_content = library_entities[entity]
        for other_entity in entities:
            if other_entity != entity and other_entity in entity_content:
                dependency_graph[entity].add(other_entity)
    
    return dependency_graph

def topological_sort(entities, dependency_graph):
    """
    Perform topological sorting on the entities based on their dependencies.
    Returns a list of entities in order such that no entity comes before its dependencies.
    """
    # Mark all entities as not visited
    visited = {entity: False for entity in entities}
    temp_mark = {entity: False for entity in entities}
    ordered_entities = []
    
    def visit(entity):
        if temp_mark[entity]:
            # We found a cycle
            print(f"Warning: Circular dependency detected involving {entity}")
            return
        if not visited[entity]:
            temp_mark[entity] = True
            for dependency in dependency_graph[entity]:
                visit(dependency)
            temp_mark[entity] = False
            visited[entity] = True
            ordered_entities.append(entity)
    
    # Visit all unvisited entities
    for entity in entities:
        if not visited[entity]:
            visit(entity)
    
    return ordered_entities

def extract_dependencies(solution_file_path, library_file_path, output_file_path=None):
    """
    Extract the dependencies from the library and embed them in the solution file.
    If output_file_path is None, the solution file will be modified in place.
    """
    # Read the solution file
    with open(solution_file_path, 'r') as f:
        solution_content = f.read()
    
    # Check if the solution includes coding_library.h
    library_include_pattern = re.compile(r'#include\s*"coding_library.h"')
    if not library_include_pattern.search(solution_content):
        print(f"Warning: {solution_file_path} does not include coding_library.h")
        return
    
    # Read the library file
    with open(library_file_path, 'r') as f:
        library_content = f.read()
    
    # Extract all function and class definitions from the library
    library_entities = get_function_definitions(library_content)
    
    # Find which entities are used in the solution
    required_entities = find_dependencies(solution_content, library_entities)
    
    # Build dependency graph
    dependency_graph = build_dependency_graph(required_entities, library_entities)
    
    # Sort entities topologically based on dependencies
    ordered_entities = topological_sort(required_entities, dependency_graph)
    
    # Create the new solution content with dependencies
    solution_lines = solution_content.split('\n')
    
    # Find the position to insert the dependencies (after the includes)
    insert_position = 0
    for i, line in enumerate(solution_lines):
        if '#include' in line:
            insert_position = i + 1
    
    # Remove the coding_library.h include
    solution_lines = [line for line in solution_lines if not library_include_pattern.search(line)]
    
    # Insert the dependencies
    header_comment = "\n// Begin extracted dependencies from coding_library.h\n"
    footer_comment = "\n// End extracted dependencies from coding_library.h\n"
    
    dependencies_content = header_comment
    for entity in ordered_entities:
        dependencies_content += library_entities[entity] + "\n\n"
    dependencies_content += footer_comment
    
    # Reconstruct the solution file with dependencies
    new_solution_content = '\n'.join(solution_lines[:insert_position]) + \
                          dependencies_content + \
                          '\n'.join(solution_lines[insert_position:])
    
    # Write the output
    if output_file_path is None:
        output_file_path = solution_file_path
    
    with open(output_file_path, 'w') as f:
        f.write(new_solution_content)
    
    print(f"Dependencies extracted and written to {output_file_path}")
    print(f"Extracted {len(required_entities)} entities: {', '.join(sorted(required_entities))}")
    print(f"Ordered for dependencies: {', '.join(ordered_entities)}")

def main():
    parser = argparse.ArgumentParser(description='Extract dependencies from coding_library.h into solution files')
    parser.add_argument('solution_file', help='Path to the solution file')
    parser.add_argument('--library', default='coding_library.h', help='Path to the coding_library.h file (default: coding_library.h)')
    parser.add_argument('--output', help='Output file path (default: overwrites the solution file)')
    
    args = parser.parse_args()
    
    extract_dependencies(args.solution_file, args.library, args.output)

if __name__ == "__main__":
    main() 