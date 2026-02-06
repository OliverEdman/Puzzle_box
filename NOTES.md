
  KOPPLINGSSCHEMA (DISPLAY & SKIFTREGISTER)

 * FRÅN (74HC595)        TILL (ARDUINO/BREADBOARD)      FUNKTION
 
 * Pin 16 (VCC)          5V (Röd skena)                 Strömförsörjning
 * Pin 8  (GND)          GND (Blå skena)                Jord
 * Pin 10 (SRCLR)        5V (Röd skena)                 Reset (Inaktiv)
 * Pin 13 (OE)           GND (Blå skena)                Output Enable (Aktiv)
 * Pin 14 (SER)          PB3 (Digital 11 / MOSI)        Data-in
 * Pin 11 (SRCLK)        PB5 (Digital 13 / SCK)         Klocka
 * Pin 12 (RCLK)         PB2 (Digital 10 / SS)          Latch (Visa data)

  UTGÅNGAR TILL DISPLAY (Via 220 ohm motstånd):

 * Pin 15 (Q0)           Display Segment A              Topp
 * Pin 1  (Q1)           Display Segment B              Uppe Höger
 * Pin 2  (Q2)           Display Segment C              Nere Höger
 * Pin 3  (Q3)           Display Segment D              Botten
 * Pin 4  (Q4)           Display Segment E              Nere Vänster
 * Pin 5  (Q5)           Display Segment F              Uppe Vänster
 * Pin 6  (Q6)           Display Segment G              Mitten



SHIFR REGISTER LOGIK



DATA (DS/MOSI) 

Bestämmer om nästa bit ska vara hög eller låg. Jag Har 0b00101100 för port b till min display.

CLOCK (SCK)

Denna pinnen säger åt data när det är dags för nästa bit så CLOCK tittar är biten låg eller hög just nu?
Sedan skickar informationen till data och säger okej skicka nästa bit och tittar igen om den är hög eller låg tills man tittar på alla bitar sedan skickar vi detta värde 00101100 till Latch.

LATCH

Efter clock är klar och säger okej tack jag har sparat alla 8 bitar i rätt ordning skickas detta till latch som fungerar som en dörr eller fryser displayen för att inte ska flimra.
 latch har fått 8 bitar information från CLOCK OCH DATA och LATCH visar nu på display och sen stänger dörren när nästa information kommer alltså 8 bitar så öppnar den dörren och visar detta på display om och om igen jätte fort och stänger dörren mellan varje 8 bitar information för att inte displayen ska flimra






