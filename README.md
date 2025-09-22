# Horloge-3-modes

https://github.com/user-attachments/assets/84a211e7-d904-4713-ae11-0fa4f5635c76

Horloge 3 modes, sur ST7735 version analogique et numérique et avec DF player pour la lecture des fichiers sonores. Le tout piloté par du ESP32C3 super mini. La mise à l'heure de fait au démarrage par accès au serveur NTP et réglage de la zone horaire. Par le suite l'horloge est pilotée par l'horloge interne de l'ESP cela permet de s'affranchir du wifi en fonctionnement. En cas de dérive ou pour la mise ou remise à l'heure il suffit de redémarrer l'horloge à proximité du réseau wifi.
