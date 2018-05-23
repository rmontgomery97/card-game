# card-game
SImple card game loosely based on the game of cricket.

The rules are simple. When batting, if you play a card of the same suit with a higher number, you score runs depending on how much higher the number than the one bowled. If you play a card with the same number but different suit, no wicks are lost but no runs are scored. The inning is over once you lose 10 wicks.

When bowling, if you play a card the same number or one higher as the previously bowled card, a run is scored.

If you would like to create your own agent, just create a file in the same directory containing a function that begins with "ccgAgent" follwed by your chosen agent name.

To build and run the simulation, enter the following commands from the command line:

```
nice bash ccgBuild.bash
nice ./ccgRunSim
```
