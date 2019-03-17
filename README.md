# cs467 capstone

## Text Based Murder Mystery in C++

- Kendal Droddy
- Matt Garner
- Rozalija Zibrat


# Compilation and Usage instructions

"make all" will make the current state of the game

"./gamedriver" will run the current state of the game 

# clean

"make clean" will remove the executable and the object files create durin compilation


# Game Instructions

Murder Mystery features 16 rooms spread over four distinct game map areas. Each room contains multiple items which can be 
interacted with in a variety of ways. In some cases, items may be interacted with in a way that changes the environment and 
revealing additional items. These items can be picked up and added to the player’s inventory. They may also be dropped in any 
other room and picked up again at a later point. Put your detective hat on and examine your surroundings, gather and analyze 
evidence, interrogate suspects and ultimately accuse the true criminal.


## Game Commands
The game’s language parser recognizes a variety of commands. Discover them yourself or consult the table below for a full list of commands. 
Please note that multiple actions can be handled e.g., “Go to the kitchen and drop the photograph.” Also note that <object> denotes both an item and a 
feature in the game.


Go **room/direction** or Move **room/direction** or **room** or **direction**

Use this command to move from room to room


Inspect **object** or Examine **object** or Look **object** or search **object**

Take a closer look at items, objects, or people within rooms


Take **Item**

Take an item and add it to your inventory


Drop **Item**

Drop an object in a room, leaving it for later. Drop multiple items at once by separating them with commas.


Sample **Feature**

Sample some evidence, such as blood, to take back to the Forensics Lab


Analyze **item**

Analyze an item to gain valuable insight - must be in Forensics Lab


Hack **Feature**

Break into certain electronic devices


Listen **Object** or play **Object**

Listen to certain devices


Interrogate **person**

Ask the tough questions


Clear **person**

Declare a suspect innocent - if you’ve gathered enough evidence to do so


Accuse **person**

Serve justice to the murderer - clear the innocent suspects first


Ask **person** about **item**

Get some context on what you’ve found


Talk **person**

Interact with people you encounter 


Help
 
Display the actions you can take


Inventory 

Display all items currently in your inventory


Look

Repeats the room’s long description


Save

Save the game in its current state to return to later


Load

Load in a previously saved game


Reflect

Get a brief overview of what you’ve learned so far

