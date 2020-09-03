# Try-to-hit-me

This repository holds the c++ side of Unreal Engine 4 project of a study of the concepts and tools used to develop an AI. In a 1 vs 1 shooter, the enemy AI patrols or reacts to the player chasing him or flanking him from outside of the player’s view.

Here BaseCharacter describes some basic properties used in the game as the health and the team ID. 
AIC_Enemy is the AI Controller used for the enemy and describes the initialization of the Perception component and the Sight Sense configuration while also handling the case when the player is perceived. This class is linked to a Behaviour Tree Blueprint and a Blackboard that are updated according to the values obtained using perception.

