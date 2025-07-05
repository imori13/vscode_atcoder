const { spawn } = require('child_process');
const fs = require('fs');
const path = require('path');

const sourceFile = process.argv[2] || 'main.cpp';
const baseName = path.basename(sourceFile, '.cpp');
const inputFile = 'src/input.txt';

console.log(`Running ${sourceFile} with Docker...`);

// Docker環境で実行
const dockerRun = spawn('docker-compose', [
    'exec', '-T', 'atcoder',
    'bash', '-c', `./output/${baseName} < ${inputFile}`
], {
    stdio: 'inherit',
    cwd: process.cwd()
});

dockerRun.on('close', (code) => {
    console.log(`Process exited with code ${code}`);
    process.exit(code);
});

dockerRun.on('error', (err) => {
    console.error('Failed to run Docker command:', err);
    process.exit(1);
});