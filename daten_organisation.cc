//Dieses Programm ist in Pseudocode geschrieben. Das Format ist nur .cc, da 
//ich so ein paar Färbungen von meinem Editor beibehalten kann ;)






//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~DATENTYPEN~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

enum bundesland_kuerzel { bayern, nrw, baden-württemberg, hessen, sachsen, niedersachsen /*usw.*/ }

class infos {
	int neuinfektionen //letzte 24h
	int gesamtinfektionen
	int verstorben
}

class zeit {
	int tag
	int monat
	int jahr
}

class bundesland {
	string name //des bundeslands

	//array/vector, der jeweils das Datum der Tage hält, dient zur Übersicht, von welchen Tagen wir überhaupt infos haben
	zeit[] datum 

	//dies ist der wichtigste Inhalt  der Klasse Bundesland: eine Map, die durch Eingabe eines Datums Infos zurückliefert.
	//Beispiel in C++ (geht in anderen Sprachen ähnlich einfach, nur kenne ich die Syntax nicht): 
	//
	//	wollen wir die infos vom 27.09.2020 --> infos x = zahlen[27.09.2020];
	//
	//Dies ist sehr einfach handzuhaben und von der Laufzeit sehr effizient.
	map <zeit, infos> zahlen 

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~








//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~FÜR ANDERE WICHTIG~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//ein Array/Vector, das alle Bundesländer hält. 
//Bayern hat z.B. index = 0, nrw = 1, baden-württemberg = 2, hessen = 3, sachsen = 4, niedersachsen = 5 usw. 
//(muss festgelegt sein, durch enums schöner: siehe oben -> Datentypen
bundesland[16] deutschland

//diese Funktion wird jeden Tag aufgerufen, um das aktuelle Datum und die passenden neuen Zahlen auf den neuesten Stand zu bringen
function new_day() {
	//für jedes Bundesland holen wir uns die Infos aus der Datenbank für den neuen Tag
	for (int i = 0; i < 16; i++) {
		
		//wir denken uns eine Funktion, die uns das aktuelle Datum gibt (von Sprache zu Sprache unterschiedlich)
		zeit heute = get_datum() 

		//eine ausgedachte Funktion, die (je nach Container, ob Array oder Vektor etc.) ein neues Element am Ende einfügt 
		//(vgl.: C++-Vektor: push_back())
		deutschland[i].datum.add_at_the_end(heute.tag, heute.monat, heute.jahr)

		//ein Element von infos, das die aktuellsten Infos hält
		infos zahlen_heute

		//dies ist sind ausgedachte Funktionen, um Infos aus der Datenbank zu bekommen. Wie genau dies umgesetzt wird, 
		//mach ich noch mit Cem aus ;) )
		zahlen_heute.neuinfektionen = get_from_datenbank(heute, deutschland[i].name, neuinfektionen) 
		zahlen_heute.gesamtinfektinoen = get_from_datenbank(heute, deutschland[i].name, gesamtinfektionen)
		zahlen_heute.verstorben = get_from_datenbank(heute, deutschland[i].name, verstorben)

		//nun fügen wir die aktuellsten Infos (zahlen_heute) in die Hashmap, verbunden mit dem Datum, ein
		deutschland[i].zahlen.add(heute, zahlen_heute)
	}

}

//Funktionen, die den Zugriff erleichtern, also mit denen man einfach an die gewünschten Zahlen kommt
//(vielleicht für unsere Webseite-Leute das Wichtigste :) )

//Eingabe-Beispiel: int zahl = get_neuinfektionen(bayern, 27, 9, 2020); --> gibt Neuinfektionen vom 27.09.2020 in Bayern aus. 
//Easy, oder? ;)
function int get_neuinfektionen(bundesland_kuerzel land, int tag, int monat, int jahr) {
	zeit x
	x.tag = tag
	x.monat = monat
	x.jahr = jahr

	return deutschland[land].zahlen[x].neuinfektionen
}

function int get_gesamtinfektionen(bundesland_kuerzel land, int tag, int monat, int jahr) {
	zeit x
	x.tag = tag
	x.monat = monat
	x.jahr = jahr

	return deutschland[land].zahlen[x].gesamtinfektionen
}

function int get_verstorbene(bundesland_kuerzel land, int tag, int monat, int jahr) {
	zeit x
	x.tag = tag
	x.monat = monat
	x.jahr = jahr

	return deutschland[land].zahlen[x].verstorbene
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~










//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~BEISPIEL~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//Will man die Infos von Bayern von den letzten 14 Tagen nacheinander ausgegeben haben

for (int i = 1; i <= 14; i++) {
	zeit x = deutschland[bayern].datum;
	//wir gehen alle die letzten 14 Daten von oben durch, also das aktuellste Zuerst, und geben die dazu passenden Infos jeweils nacheinander aus
	print(get_neuinfektionen(bayern, x.tag, x.monat, x.jahr)
	print(get_gesamtinfektionen(bayern, x.tag, x.monat, x.jahr)
	print(get_verstorbene(bayern, x.tag, x.monat, x.jahr)
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~









//~~~~~~~~~~~~~~~~~~~~~~~~~~~~NOCH~EIN~FESCHES~BEISPIEL~LOL~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//Will man die aktuellsten Neuinfektionen alles Bundesländer (z.B. für einen Vergleich)

for (int i = 0; i < 16; i++) {
	zeit x = deutschland[i].datum[datum.size - 1] //aktuellstes Datum, da jedes neue hinten angehängt wird ;)

	print(bundesland[i].namen)

	print(bundesland[i].zahlen[x].neuinfektionen)
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~










//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~EPILOG~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Meiner Meinung nach ist das eine gute Verwaltung der Daten.

Vorteile:
	- effizient (der häufigste Zugriff wird vermutlich auf die Hashmap sein). Hashmaps sind eine sehr effiziente Möglichkeit, 
	  auf Informations-Paare zuzugreifen, da der Key (das Datum) mit den Values (den Infos/Zahlen) direkt verknüpft sind und 
	  somit nicht in einem Array oder so danach gesucht werden muss.
	- recht einfache Bedienung. Im Grunde sind nur die 3 Haupt-Funktionen für die Anderen von Wichtigkeit. Diese lassen eine 
	  recht einfache Bedienung zu.
	- Auch der Zugriff auf die einzelnen Bundesländer erfolgt ohne Durch-Iterieren durch das Deutschland-Array, da man direkt 
	  durch das Enum auf die passenden Elemente zugreifen kann. Auch das ist effizient.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
