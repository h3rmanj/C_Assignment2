Herman Jensen

KODE
Jeg delte inn oppgaven 3 filer. Først asciitable, som inneholder structen AsciiTable, og en metode som returnerer AsciiTable sin data som en hel string.
Deretter har jeg dirscanner, som er en hjelpeklasse til asciitable. Den har en "public" metode i headeren som returnerer en AsciiTable utifra et directory.
Dirscanner søker gjennom directory etter parts som tilhører directorynavnet. Dvs hvis brukeren har tukla og har parts til wolf i mickey vil de bli ignorert, samme gjelder filer som ikke er parts.
Deretter begynner den å sette opp en AsciiTable ved å se hvor mange rader og kolonner asciien er splittet opp i, og leser alle filene og lagerer de i AsciiTablet.
Assignment2.c inneholder main-metoden, som først kjører metoden scanDir, og deretter sender AsciiTable til mergeAsciiTable, og printer eller lagerer char* den får fra den.

BRUK
Lag programmet:
gcc asciitable.c dirscanner.c assignment2.c -o ascii.h
Det første argumentet til programmet er directoryet som inneholder partsene. Det andre argumentet er filen den skal lagre resultatet i, har man ikke argument 2 printer den resultatet i terminalen.
Eksempler:
./ascii.o mickey/
./ascii.o wolf result.txt

REFLEKSJON
Jeg er fornøyd med at jeg fikk til å lage ett program som klarer å lese mappene dynamisk, og ikke bare hardkoda f.eks. måten å lage mickey.
Har ikke testa det, men hvis en part mangler antar jeg at det blir feil, fordi jeg ikke sjekker om den får noe data tilbake når den leser filene.
Ytelsesmessig burde jeg delt inn hver part i 30x30 når jeg leser, istedenfor å substringe 30 av gangen når jeg setter alle partene sammen.
