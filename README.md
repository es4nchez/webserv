# webserv
HTTP server in C++ 98

Première ébauche de plan :

- Regarder commment gérer les socket en cpp98 et regarder ce qu'on peut utiliser

- Créer une fonction qui crée un socket et le bind sur un port spécifique. La fonction attendra des connexions entrantes.

- Créer une fonction qui prends les connections entrantes et lis les data de la socket. Elle parse la requête HTTP et détermine la réponse appropriée

- Créer une fonction qui envoi la réponse au client, avec les corrects HEADERS et le BODY de réponse.

- Le tout dans une boucle while qui attends les connections pour y répondre

- Time to testing
