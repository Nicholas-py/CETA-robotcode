//Adafruit configs
#define _LMotor "ChessPlayer/feeds/cetaiotrobot31415.lmotor"
#define _RMotor "ChessPlayer/feeds/cetaiotrobot31415.rmotor"

#define _LSensor "ChessPlayer/feeds/cetaiotrobot31415.lmotor"
#define _CSensor "ChessPlayer/feeds/cetaiotrobot31415.cmotor"
#define _RSensor "ChessPlayer/feeds/cetaiotrobot31415.rmotor"

#define _Commands "ChessPlayer/feeds/cetaiotrobot31415.commands"
#define _Start "ChessPlayer/feeds/cetaiotrobot31415.start"

#define _ClientID "ea182fe498d648b8a8351534ac82f23b"
#define _Username "ChessPlayer"

//Settings for debugging
bool _ShouldCalibrate = true;
bool _StopAfterFourTurns = true;
bool _shouldConnectToHQTTC = false;
bool _ShouldStopAtWall = false;

//Movement Logic
enum PossibleLineFollowingLogics {NICHOLAS, MUNJAL, ADRIAN}; //Adrian: 44s, Munjal: unknown, Nick: 27s
enum PossibleLineFollowingLogics _CurrentLineFollowingLogic = ADRIAN;
