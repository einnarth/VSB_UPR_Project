README

Popis programu
    Vytvoril som program, ktorý na základe vstupných parametrov sa snazí predpovedať šírenie epidémie pomocou modelu SIR a následne ich porovná s dátami z CSV súboru.
    Tieto výsledky sa zobrazia na grafe, reálne dáta sú plnou čiarou a dáta z modelu čiarkovanou.

Postup programu
    1. Program si vyselectuje parametre z príkazu a uloží ich.
    2. Následne si otvorí CSV súbor, prečíta ho a uloží si dáta.
    3. Program si vytvorí premenné ktoré potrebuje na výpočeť SIR modelu.
    4. Program simuluje pomocou modelu SIR, ukladá pomery do dynamicky alokovaného poľa.
    5  Nakreslí sa graf (Reálne dáta sa prevádzaju do pomeru).

Spustenie programu
    1. V termináli si otvoríme priečinok kde sa nachádza kód a napíšeme "make".
    2. Pre spustenie odporúčam použiť príkaz: ./epidemic --real_data test.csv --infectious_days 8 --infections_per_day 0.3 --output graf.svg
    3. Tento príkaz používa parametre obdobné chorobe Covid-19 a má CSV súbor s dátami z 1000 obyvateľov počas 31dní.

Poznámka:
    V kóde sa pri generácii grafu často používajú pretypovania double a int, double sa používa pre výpočet mierky a pomeru, int sa používa pre vykreslenie pixelov.
