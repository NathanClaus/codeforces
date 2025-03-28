const canvas = document.getElementById('canvas');
const ctx = canvas.getContext('2d');

// Scale factor to make the visualization more visible
const SCALE = 50;
const OFFSET_X = canvas.width / 2;
const OFFSET_Y = canvas.height / 2;

// Sample test case
let points = [
    { x: 0, y: 0 },
    { x: 2, y: 0 },
    { x: 0, y: 1 }
];

let animationState = {
    currentStep: 0,
    isAnimating: false,
    currentPoint: 0,
    currentDirection: 0
};

const deltax = [1, 0, -1, 0];
const deltay = [0, 1, 0, -1];

// Function to generate random integer in range [min, max]
function randomInt(min, max) {
    return Math.floor(Math.random() * (max - min + 1)) + min;
}

// Function to generate random point within visible range
function generateRandomPoint() {
    // Calculate visible range based on canvas size and scale
    const maxX = Math.floor((canvas.width / 2) / SCALE);
    const maxY = Math.floor((canvas.height / 2) / SCALE);
    return {
        x: randomInt(-maxX, maxX),
        y: randomInt(-maxY, maxY)
    };
}

// Function to check if points are too close to each other
function arePointsTooClose(p1, p2) {
    return Math.abs(p1.x - p2.x) < 1 && Math.abs(p1.y - p2.y) < 1;
}

function generateRandomTriangle() {
    // Stop any ongoing animation
    animationState.isAnimating = false;
    
    // Generate first point
    let newPoints = [generateRandomPoint()];
    
    // Generate second point
    let secondPoint;
    do {
        secondPoint = generateRandomPoint();
    } while (arePointsTooClose(newPoints[0], secondPoint));
    newPoints.push(secondPoint);
    
    // Generate third point
    let thirdPoint;
    do {
        thirdPoint = generateRandomPoint();
    } while (arePointsTooClose(newPoints[0], thirdPoint) || 
             arePointsTooClose(newPoints[1], thirdPoint));
    newPoints.push(thirdPoint);
    
    // Update points and redraw
    points = newPoints;
    draw();
}

function drawPoint(x, y, color = 'red') {
    ctx.beginPath();
    ctx.arc(x, y, 5, 0, 2 * Math.PI);
    ctx.fillStyle = color;
    ctx.fill();
    ctx.stroke();
}

function drawLine(x1, y1, x2, y2, color = 'blue') {
    ctx.beginPath();
    ctx.moveTo(x1, y1);
    ctx.lineTo(x2, y2);
    ctx.strokeStyle = color;
    ctx.stroke();
}

function drawTriangle(points, color = 'blue') {
    for (let i = 0; i < 3; i++) {
        const p1 = points[i];
        const p2 = points[(i + 1) % 3];
        drawLine(
            p1.x * SCALE + OFFSET_X,
            p1.y * SCALE + OFFSET_Y,
            p2.x * SCALE + OFFSET_X,
            p2.y * SCALE + OFFSET_Y,
            color
        );
    }
}

function drawGrid() {
    ctx.strokeStyle = '#ddd';
    ctx.lineWidth = 0.5;
    
    for (let x = 0; x < canvas.width; x += SCALE) {
        ctx.beginPath();
        ctx.moveTo(x, 0);
        ctx.lineTo(x, canvas.height);
        ctx.stroke();
    }
    
    for (let y = 0; y < canvas.height; y += SCALE) {
        ctx.beginPath();
        ctx.moveTo(0, y);
        ctx.lineTo(canvas.width, y);
        ctx.stroke();
    }
}

function draw() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    drawGrid();

    // Draw the current triangle
    drawTriangle(points);

    // Draw points
    points.forEach(point => {
        drawPoint(
            point.x * SCALE + OFFSET_X,
            point.y * SCALE + OFFSET_Y
        );
    });

    // Draw current animation state
    if (animationState.isAnimating) {
        const currentPoint = points[animationState.currentPoint];
        const tempPoint = {
            x: currentPoint.x + deltax[animationState.currentDirection],
            y: currentPoint.y + deltay[animationState.currentDirection]
        };
        
        // Draw temporary point being tested
        drawPoint(
            tempPoint.x * SCALE + OFFSET_X,
            tempPoint.y * SCALE + OFFSET_Y,
            'green'
        );
        
        // Draw temporary triangle
        const tempPoints = [...points];
        tempPoints[animationState.currentPoint] = tempPoint;
        drawTriangle(tempPoints, 'green');
    }
}

function checkRightTriangle(p1, p2, p3) {
    const ab = { x: p2.x - p1.x, y: p2.y - p1.y };
    const ac = { x: p3.x - p1.x, y: p3.y - p1.y };
    const bc = { x: p3.x - p2.x, y: p3.y - p2.y };

    if (ab.x * ac.x + ab.y * ac.y === 0) return true;
    if (ac.x * bc.x + ac.y * bc.y === 0) return true;
    if (bc.x * ab.x + bc.y * ab.y === 0) return true;
    return false;
}

function animate() {
    if (!animationState.isAnimating) return;

    const currentPoint = points[animationState.currentPoint];
    const tempPoint = {
        x: currentPoint.x + deltax[animationState.currentDirection],
        y: currentPoint.y + deltay[animationState.currentDirection]
    };

    const tempPoints = [...points];
    tempPoints[animationState.currentPoint] = tempPoint;

    if (checkRightTriangle(...tempPoints)) {
        animationState.isAnimating = false;
        alert('ALMOST RIGHT triangle found!');
        return;
    }

    animationState.currentDirection++;
    if (animationState.currentDirection >= 4) {
        animationState.currentDirection = 0;
        animationState.currentPoint++;
        if (animationState.currentPoint >= 3) {
            animationState.isAnimating = false;
            alert('NEITHER RIGHT nor ALMOST RIGHT triangle');
            return;
        }
    }

    draw();
    setTimeout(animate, 1000);
}

function startAnimation() {
    if (checkRightTriangle(...points)) {
        alert('RIGHT triangle!');
        return;
    }

    animationState = {
        currentStep: 0,
        isAnimating: true,
        currentPoint: 0,
        currentDirection: 0
    };
    animate();
}

function resetAnimation() {
    animationState.isAnimating = false;
    draw();
}

// Initial draw
draw(); 