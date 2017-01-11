Zorg dat de code in de sketch op de arduino draait.
Zorg dat er een LED geprikt zit in Pin 13.
Sluit de arduino voor stroom aan (bijvoorbeeld aan raspberry Pi)

Vanuit code, gebruik het volgende om de led aan of uit te zetten:

LedController::getInstance().turnLed(true);

LedController::getInstance().turnLed(false);

Voor een test, ga in de Gpio folder en 'make'. Zet vervolgens 'controller' binary op de Raspberry Pi en run deze. (blink 1 sec interval)