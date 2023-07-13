BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS `toast` (
	`id`	INTEGER PRIMARY KEY AUTOINCREMENT,
	`text`	TEXT
);
INSERT INTO `toast` VALUES (1,'Piłka, bramka, gol');
INSERT INTO `toast` VALUES (2,'Co by nam się!');
INSERT INTO `toast` VALUES (3,'Pije Kuba do Jakuba');
INSERT INTO `toast` VALUES (4,'Chluśniem, bo uśniem!');
INSERT INTO `toast` VALUES (5,'Za drzewa, z których zrobią nasze trumny... Żeby jeszcze długo rosły');
INSERT INTO `toast` VALUES (6,'No to chlup w ten głupi dziób');
INSERT INTO `toast` VALUES (7,'Za matki naszych dzieci - co by były piękne');
INSERT INTO `toast` VALUES (8,'Na prawą nożkę');
INSERT INTO `toast` VALUES (9,'Na lewą nóżkę');
INSERT INTO `toast` VALUES (10,'Łykniem, bo odwykniem!');
INSERT INTO `toast` VALUES (11,'Rach ciach babka w piach');
INSERT INTO `toast` VALUES (12,'Moja babcia chorowała - piła wódkę - wyzdrowiała');
INSERT INTO `toast` VALUES (13,'Idzie osioł przez pustynie. Idzie dzień, drugi, trzeci... Słońce praży, osła meczy pragnienie. Nagle widzi: stoją dwie wielkie beczki - jedna z woda, druga z wódka. Z której zaczął pić? Oczywiście z pierwszej! Nie bądźmy więc osłami i napijmy się wódki!');
INSERT INTO `toast` VALUES (14,'Płynie przez rzekę żółw, a na jego grzbiecie zwinął się jadowity wąż. Wąż myśli: ''Ugryzę - zrzuci''. Żółw myśli: ''Zrzucę - ugryzie''. Wypijmy za nierozerwalna przyjaźń, co znosi wszelkie przeciwności!');
INSERT INTO `toast` VALUES (15,'Pijmy, bo szkłem przejdzie');
INSERT INTO `toast` VALUES (16,'Szable w dłoń');
INSERT INTO `toast` VALUES (17,'Słońce świeci, ptasze kwili... Może byśmy się napili?');
INSERT INTO `toast` VALUES (18,'No to cyk (powiedział budzik do zegara)');
INSERT INTO `toast` VALUES (19,'Uchyl się duszo, bo ulewa idzie');
INSERT INTO `toast` VALUES (20,'Buch go w migdał, aby krzyk dał');
INSERT INTO `toast` VALUES (21,'Osoba godna pije do dna');
INSERT INTO `toast` VALUES (22,'Kilka drinków dziennie, to zdrowe serce i marzenia senne');
INSERT INTO `toast` VALUES (23,'Za zdrowie gospodarzy! Niech zawsze mają takich fajnych gości jak dziś.');
INSERT INTO `toast` VALUES (24,'Malutki kieliszek nie dojdzie do kiszek');
INSERT INTO `toast` VALUES (25,'Polska Alkoholska, Poland - Alkoholand.');
INSERT INTO `toast` VALUES (26,'Zebraliśmy się tu po to, by sobie popić. Wypijmy za to, żeśmy się tu zebrali.');
CREATE TABLE IF NOT EXISTS `party` (
	`id`	INTEGER PRIMARY KEY AUTOINCREMENT,
	`name`	TEXT,
	`started`	TIMESTAMP,
	`ended`	TIMESTAMP
);
CREATE TABLE IF NOT EXISTS `drink_type` (
	`id`	INTEGER PRIMARY KEY AUTOINCREMENT,
	`name`	TEXT,
	`default_amount_ml`	INTEGER,
	`percentage` REAL
);
INSERT INTO `drink_type` VALUES (1,'wódka',25, 40.0);
INSERT INTO `drink_type` VALUES (2,'piwo',500, 6.0);
CREATE TABLE IF NOT EXISTS `drink` (
	`id`	INTEGER PRIMARY KEY AUTOINCREMENT,
	`drink_type_id`	INTEGER,
	`party_id`	INTEGER,
	`timestamp`	TIMESTAMP,
	`amount_ml`	INTEGER,
	`toast_id`	INTEGER,
	FOREIGN KEY(`party_id`) REFERENCES `party`(`id`) ON DELETE CASCADE,
	FOREIGN KEY(`drink_type_id`) REFERENCES `drink_type`(`id`) ON DELETE CASCADE,
	FOREIGN KEY(`toast_id`) REFERENCES `toast`(`id`)
);

CREATE TABLE IF NOT EXISTS `user` ( 
	`id` INTEGER PRIMARY KEY AUTOINCREMENT, 
	`name` TEXT, `email` TEXT,
	`admin` INTEGER
);

CREATE TABLE `user_drink` (
	`id` INTEGER PRIMARY KEY AUTOINCREMENT, 
	`user_id` INTEGER, 
	`drink_id` INTEGER, 
	FOREIGN KEY(`user_id`) REFERENCES `user`(`id`) ON DELETE CASCADE, 
	FOREIGN KEY(`drink_id`) REFERENCES `drink`(`id`) ON DELETE CASCADE
);

COMMIT;
