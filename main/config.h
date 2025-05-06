#define _Commands "ChessPlayer/feeds/cetaiotrobot31415.commands"
#define _Start "ChessPlayer/feeds/cetaiotrobot31415.start"
#define _ToServer "ChessPlayer/feeds/cetaiotrobot31415.received"

#define _ClientID "ea182fe498d648b8a8351534ac82f23b"
#define _Username "ChessPlayer"

//Settings for debugging
bool _ShouldCalibrate = true;
bool _StopAfterFourTurns = true;
bool _shouldConnectToHQTTC = false;
bool _ShouldStopAtWall = false;

//config for selecting movement code 
enum PossibleLineFollowingLogics {NICHOLAS, MUNJAL, ADRIAN, REVUP, SHOWCASE}; //Adrian: 44s, Munjal: 21a, Nick: 22s
enum PossibleLineFollowingLogics _CurrentLineFollowingLogic = NICHOLAS;
