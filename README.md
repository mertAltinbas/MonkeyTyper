<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Monkey Typer - README</title>
</head>
<body>
    <h1>Monkey Typer</h1>
    <p>Monkey Typer is a fast-paced typing game built with C++ and SFML. The goal is to type falling words before they reach the edge of the screen. The game includes a scoring system, adjustable difficulty levels, and a save/load feature for game progress.</p>
    
    <h2>Features</h2>
    <ul>
        <li><strong>Typing Challenge:</strong> Type words before they disappear.</li>
        <li><strong>Scoring System:</strong> Earn points based on word length.</li>
        <li><strong>Lives System:</strong> Lose lives for missed words.</li>
        <li><strong>Adjustable Difficulty:</strong> Choose from Easy, Medium, or Hard modes.</li>
        <li><strong>Game Save & Load:</strong> Continue where you left off.</li>
        <li><strong>Simple UI:</strong> Uses SFML for smooth rendering.</li>
    </ul>
    
    <h2>Installation & Usage</h2>
    <ol>
        <li>Clone the repository:</li>
        <pre><code>git clone https://github.com/yourusername/MonkeyTyper.git</code></pre>
        <li>Ensure you have SFML installed.</li>
        <li>Compile the project:</li>
        <pre><code>g++ -o MonkeyTyper main.cpp Game.cpp Word.cpp -lsfml-graphics -lsfml-window -lsfml-system</code></pre>
        <li>Run the game:</li>
        <pre><code>./MonkeyTyper</code></pre>
    </ol>
    
    <h2>Controls</h2>
    <ul>
        <li><strong>Type Words:</strong> Type as they appear on the screen.</li>
        <li><strong>Backspace:</strong> Delete characters.</li>
        <li><strong>Escape:</strong> Save and return to the main menu.</li>
        <li><strong>Space:</strong> Start a new game.</li>
        <li><strong>L:</strong> Load a saved game.</li>
        <li><strong>Right Shift:</strong> Open settings.</li>
        <li><strong>M:</strong> Restart after game over.</li>
    </ul>
    
    <h2>Dependencies</h2>
    <ul>
        <li><strong>SFML</strong> (Simple and Fast Multimedia Library)</li>
    </ul>
    
    <h2>License</h2>
    <p>This project is open-source and available under the MIT License.</p>
</body>
</html>
