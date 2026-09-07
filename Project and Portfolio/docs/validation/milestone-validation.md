</> Markdown



\# Milestone 1 Validation



\## Build Validation

\-	Configuration: Debug

\-	Platform: x64

\-	Build Result: Successful

\-	Errors: None

\-	Warnings: None

\-	Evidence: Successful build and runtime screenshots saved in the images folder.



\## Main Menu Validation

1\.	Test: Start Game option

\-	Expected result: Starts the game and proceeds to character naming and the opening game flow.

\-	Actual result: As expected

\-	Status: Pass

2\.	Test: Exit option

\-	Expected result: Ends program.

\-	Actual result: As expected

\-	Status: Pass

3\.	Test: Invalid input

\-	Expected result: Tells user of invalid input and requests new input.

\-	Actual result: As expected

\-	Status: Pass



\## Character Naming Validation

1\.	Test: Character name input

\-	Expected result: Takes user input for naming character.

\-	Actual result: As expected

\-	Status: Pass

2\.	Test: Name storage

\-	Expected result: Name is stored in Player object.

\-	Actual result: As expected

\-	Status: Pass

3\.	Test: Name with spaces

\-	Expected result: Name containing spaces is stored in Player object.

\-	Actual result: As expected

\-	Status: Pass



\## Camp Menu Validation

1\.	Test: View Status option

\-	Expected result: Shows all current player stats accurately.

\-	Actual result: As expected

\-	Status: Pass

2\.	Test: Sleep option

\-	Expected result: Updates hunger and hydration stats by lowering them by 10.

\-	Actual result: As expected

\-	Status: Pass

3\.	Test: Exit Game option

\-	Expected result: Ends game.

\-	Actual result: As expected

\-	Status: Pass

4\.	Test: Invalid input

\-	Expected result: Tells user of invalid input and requests new input.

\-	Actual result: As expected

\-	Status: Pass

5\.	Test: Camp menu loop

\-	Expected result: After menu option successfully does as expected returns to camp menu unless Exit game was selected.

\-	Actual result: As expected

\-	Status: Pass



\## Program Flow Validation

1\.	Test: Full Start Game flow

\-	Expected result: Character name acquisition and welcoming to the game.

\-	Actual result: As expected

\-	Status: Pass

2\.	Test: Opening narrative transition

\-	Expected result: After welcoming to game tells beginning story and explains how player arrives at the island and has a base camp.

\-	Actual result: As expected

\-	Status: Pass

3\.	Test: Return to Camp after actions

\-	Expected result: After each menu option returns to Camp menu unless Exit Game was selected.

\-	Actual result: As expected

\-	Status: Pass



\## Testing Evidence		

\-	Lost Isle test run.png  -  Initial successful program execution.

\-	Main Menu.png  -  Main menu displays properly.

\-	Menu 1 test.png  -  Start Game branch test.

\-	Menu 2 test.png  -  Exit branch test.

\-	Start Game test.png  -  StartGame() function reached successfully.

\-	Camp Menu.png  -  Character naming, opening narrative, and Camp menu transition.

\-	Initial player status check.png  -  Initial player stats display correctly.

\-	Initial Sleep check.png  -  Sleep decreases Hunger and Hydration by 10.

\-	Program Exits on request.png  -  Camp Exit Game option end program correctly.

