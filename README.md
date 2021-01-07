# HuntTheWumpus
Hunt the Wumpus in C++

This is a replica of the text-based game Hunt The Wumpus from 1972, done as an excercise from Bjarne Stroustrup's book Programming Principles and Practice Using C++, therefore it was
made only for educational purposes. All the source code is provided bellow.

  You are a hunter in a 20-room cave. Each room is linked to other 3 (random) rooms. The map has the shape of a squashed dodechaderon. Your objective is to blindly move through the caves
and, using your sharp hunter senses, find and kill the horrific Wumpus that wonders in the labyrinth, with an arrow.  
Aside from the wumpus, there are 2 more enemies

  - SuperBats 
    - are spawned at random on the map
    - you can hear the noises they make from one room away ("A bat is nearby.")
    - if you enter a room with a bat, the bat might either take you to another random room (also moving itself to another random room) or ignore you.
    - beware that the chance of the bat taking you increase each time you enter its room
    - they DO NOT alert the Wumpus, but can take you in the Wupmus' room!
    
  - Slime Pits
    - are spawned at random on the map
    - you can sense a draft from one room away ("I feel a draft.")
    - if you enter a room with a Slime Pit, it's Game Over
    
  - Wumpus
    - is spawned randomly on the map
    - you can smell it from one room away ("I smell a Wumpus.")
    - if you enter the room the Wumpus is in, it's Game Over
    - it can be shot, resulting in a Win
      - but beware, each missed arrow shot alerts the Wumpus, which moves to a random adjacent room
      
    
  You, the Hunter, are equipped with your sharp hunter senses and a bow with limited amount of arrows.
    - you can either MOVE to an adjacent room or (M room_number)
    - SHOOT in up to 3 rooms (S room_numbers)
    - if you run out of arrows, the Wumpus automatically kills you.
    
GLHF at Hunting!
Quick notes:
  As default, the map's rooms are linked the same way and the player always spawns in the topmost room of the first row (see how a dodechaderon looks like).!
  Also, the third connection is always to a room on a superior / inferior row.
Use this to your advantage.

Author comments:
  I really enjoyed working at this little project because:
    1. I was able to practice and really understand how to use the information gathered so far about programming, how to (soon) complete a small project, how to hunt bugs
    2. It was an interesting experience to research and learn about how older games worked.
    3. Even if it's just a text-based game, I programmed my own game from scratch!
