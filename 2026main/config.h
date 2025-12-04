#define _Commands "ChessPlayer/feeds/cetaiotrobot31415.commands"
#define _Start "ChessPlayer/feeds/cetaiotrobot31415.start"
#define _ToServer "ChessPlayer/feeds/cetaiotrobot31415.received"
#define _TurnDirection "ChessPlayer/feeds/cetaiotrobot31415.direction"

#define _ClientID "ea182fe498d648b8a8351534ac82f23b"
#define _Username "ChessPlayer"

//Settings for debugging
bool _ShouldCalibrate = false;
bool _StopAfterFourTurns = false;
bool _shouldConnectToHQTTC = true;
bool _MQTTCStart = false;
bool _ShouldStopAtWall = true;
bool _CarnavalTurn = true;
bool _TurnOnRecive = true;
bool _ModAllSpeeds = true;

//config for selecting movement code 
enum PossibleLineFollowingLogics {NICHOLAS, MUNJAL, ADRIAN, REVUP, SHOWCASE, CARNAVAL}; //Adrian: 44s, Munjal: 21, Nick: 22s
enum PossibleLineFollowingLogics _CurrentLineFollowingLogic = CARNAVAL;
