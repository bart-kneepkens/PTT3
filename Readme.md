# Readme
Hieronder staat per map kort beschreven wat de inhoud ervan is en wat de taak van deze folders is.

### Generic Module Client:
In deze folder zit de broncode om de generieke module te bouwen. Alle verschillende module types (Plotter, Scanner, Solver, Simple Maze Printer) kunnen met deze code worden gedeployed. 

### Gpio:
In deze folder zit de Arduino code die door de Core wordt gebruikt. Tevens zit er de LEDController in, die  kan de status LED aansturen. Daarnaast is er nog een servermock aanwezig waarmee getest kan worden, die gebouwd kan worden met make.

### Graphical Maze Designer:
Dit is de grafische tool waarmee doolhoven getekend en opgeslagen naar JSON formaat kunnen worden. Is een Visual Studio project en geschreven in C#.

### Logger:
Bevat de code van de Logger, een onderdeel van de Core module dat debug berichten logt in een aparte textfile. Tevens een MockCentral en MockModule die gebruikt kunnen worden om te testen, en gebouwd worden met make.
### maze_parser:
Bevat MazeMessage klasse en code om deze objecten te (de)serializeren.

### Modules Server:
Bevat de broncode van de Core module. Hierop kunnen modules zich aanmelden en kunnen module sequenties worden gemaakt en uitgevoerd. Kan gebouwd worden met cmake.

### Plotter:
Bevat de code van de Plotter module. Implementatie hiervan is niet volledig en heeft bugs met de Motordriver. Kan gebouwd worden met cmake.

### Scanner:
Bevat de code van de Scanner module.  

### SimpleMazePrinter:
Bevat code voor een simpele testmodule die enkel het bericht naar de terminal print dat binnenkomt. Kan gebouwd worden met make.

### SocketUtils 
Deze bevat de code die zowel door de generieke module client als door de server wordt gebruikt om te communiceren.

### Solver:
Bevat de code van de Solver module. Kan gebouwd worden met make (voor generieke moduleclient) of Solver.cpp voor een standalone versie. Tests kunnen gebouwd worden met make test.