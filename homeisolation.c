#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct z
{
    double old;         // wartość u dla starego okna
    double normal;      // wartość u dla zwykłego okna
    double new;         // wartość u dla nowego okna
    double other;       // zmienna w przypadku wpisywania innego u dla okna
    double u_window;    // wspolczynnik przenikania ciepla okien
    double s_wall;      // pole powierzchni sciany
    double s_window;    // pole powierzchni okien
    double q;           // max moc pieca
    double dt;          // max roznica temperatur
    double la_wall;     // wspolczynnik lambda sciany
    double d_wall;      // grubosc sciany
    double u_wall;      // wspolczynnik przenikania ciepla sciany
    double u_isolation; // wspolczynnik przewodnictwa cieplnego izolacji
    double d_isolation; // Grubosc izolacji
    double w1;          // Wartosc u dla materialu 1
    double w2;          // Wartosc u dla materialu 2
    double w3;          // Wartosc u dla materialu 3
};

double c_window(double old, double normal, double new)
{
    int x;
    printf("U okna: \n");
    printf("1. Stare drewniane okno U = %lf\n", old);
    printf("2. Normalne okno U = %lf\n", normal);
    printf("3. Nowe okno (ciepla ramka) U = %lf\n", new);
    printf("4. Inne (wprowadz wlasne)\n");
    printf("Wybierz wpisujac numer |1|2|3|4|\n");
    printf("=================================================\nWybor = ");
    scanf("%d", &x);
    switch (x)
    {
    case 1:
        return old;
    case 2:
        return normal;
    case 3:
        return new;
    case 4:
        return 0;
    default:
        printf("Nastepnym razem wybierz poprawnie...\n");
        exit(EXIT_FAILURE);
    }
}

double c_wall(double w1, double w2, double w3)
{
    int x;
    printf("U sciany: \n");
    printf("1. Cegla ceramiczna pelna [U = %lf, d = 25cm] \n", w1);
    printf("2. Cegla ceramiczna dziurawka [U = %lf, d = 38cm]\n", w2);
    printf("3. Cegla kratowka [U = %lf, d = 38cm]\n", w3);
    printf("4. Inne (wprowadz wlasne)\n");
    printf("Wybierz wpisujac numer |1|2|3|4|\n");
    printf("=================================================\nWybor = ");
    scanf("%d", &x);
    switch (x)
    {
    case 1:
        return w1;
    case 2:
        return w2;
    case 3:
        return w3;
    case 4:
        return 0;
    default:
        printf("Nastepnym razem wybierz poprawnie...\n");
        exit(EXIT_FAILURE);
    }
}

double c_wall2()
{
    int x;
    printf("Wprowadzasz: \n");
    printf("1. Wspolczynnik U.\n");
    printf("2. Wspolczynniki lambda i grubosc sciany.\n");
    printf("Wybierz wpisujac numer |1|2|\n");
    printf("=================================================\nWybor = ");
    scanf("%d", &x);
    switch (x)
    {
    case 1:
        return 1;
    case 2:
        return 0;
    default:
        printf("Nastepnym razem wybierz poprawnie...\n");
        exit(EXIT_FAILURE);
    }
}

double findu_iso(struct z Z)
{
    double result;
    result = ((((Z.s_wall - Z.s_window) * Z.dt) / (Z.q - (Z.u_window * Z.s_window * Z.dt))) - (1 / Z.u_wall)) * Z.u_isolation;
    return result;
}

double find_q(struct z Z)
{
    double result;
    result = (((Z.s_wall - Z.s_window) * Z.dt) / ((1 / Z.u_wall) + (Z.d_isolation / Z.u_isolation))) + (Z.u_window * Z.s_window * Z.dt);
    return result;
}

int main()
{
    /*Deklaracja zmiennych*/
    struct z Z;
    double result;
    int w;
    Z.old = 2.6;
    Z.normal = 0.8;
    Z.new = 0.7;
    Z.w1 = 1.944;
    Z.w2 = 1.246;
    Z.w3 = 1.151;
    /*Wczytanie zmiennych*/
    printf("=================================================\n");
    printf("Wczytywanie zmiennych\n");
    printf("=================================================\n");
    printf("Pole powierzchni scian (razem z oknami) [m^2] = ");
    scanf("%lf", &Z.s_wall);
    if (Z.s_wall <= 0)
    {
        printf("Err : Wartosc nie moze byc ujemna.\n");
        return 0;
    }
    printf("Pole powierzchni okien [m^2] = ");
    scanf("%lf", &Z.s_window);
    if (Z.s_window < 0)
    {
        printf("Err : Wartosc nie moze byc ujemna.\n");
        return 0;
    }
    if (Z.s_window > Z.s_wall)
    {
        printf("=================================================\n");
        printf("   Powierzchnie okien i scian sie nie zgadzaja!\n");
        printf("=================================================\n");
        return 0;
    }
    printf("Max roznica temperatur = ");
    scanf("%lf", &Z.dt);
    if (Z.dt < 0)
    {
        printf("Err : Wartosc nie moze byc ujemna.\n");
        return 0;
    }
    else if (Z.dt == 0)
    {
        printf("Jesli roznica temperatur jest rowna zero to po co Ci izolacja lub ogrzewanie???\n");
        return 0;
    }
    printf("Wspolczynik przewodnictwa cieplnego materialu izolacji [W/(m * K)] = ");
    scanf("%lf", &Z.u_isolation);
    if (Z.u_isolation <= 0)
    {
        printf("Err : Wartosc nie moze byc ujemna.\n");
        return 0;
    }
    printf("=================================================\n");
    result = c_window(Z.old, Z.normal, Z.new);
    if (result)
    {
        Z.u_window = result;
    }
    else
    {
        printf("Wspolczynnik przenikania ciepla [W/(m^2 * K)] = ");
        scanf("%lf", &Z.u_window);
        if (Z.u_window <= 0)
        {
            printf("Err : Wartosc nie moze byc ujemna.\n");
            return 0;
        }
    }
    result = c_wall(Z.w1, Z.w2, Z.w3);
    if (result)
    {
        Z.u_wall = result;
    }
    else
    {
        result = c_wall2();
        if (result)
        {
            printf("Wspolczynnik U sciany [W/(m^2 * K)] = ");
            scanf("%lf", &Z.u_wall);
            if (Z.u_wall <= 0)
            {
                printf("Err : Wartosc nie moze byc ujemna.\n");
                return 0;
            }
        }
        else
        {
            printf("Wspolczynnik lambda sciany [W/(m^2 * K)] = ");
            scanf("%lf", &Z.la_wall);
            if (Z.la_wall <= 0)
            {
                printf("Err : Wartosc nie moze byc ujemna.\n");
                return 0;
            }
            printf("Grubosc sciany [cm] = ");
            scanf("%lf", &Z.d_wall);
            if (Z.d_wall <= 0)
            {
                printf("Err : Wartosc nie moze byc ujemna.\n");
                return 0;
            }
            Z.d_wall /= 100;
            Z.u_wall = Z.la_wall / Z.d_wall;
        }
    }
    printf("=================================================\n");
    printf("Jaka operacja cie interesuje?\n1. Wyliczanie grubosci izolacji\n2. Wyliczanie mocy pieca\n");
    printf("=================================================\nWybor = ");
    scanf("%d", &w);
    switch (w)
    {
    case 1:
    {
        printf("Podaj moc pieca.\n");
        printf("P [W] = ");
        scanf("%lf", &Z.q);
        if (Z.q <= 0)
        {
            printf("Err : Wartosc nie moze byc ujemna.\n");
            return 0;
        }
        result = findu_iso(Z);
        break;
    }
    case 2:
    {
        printf("Podaj grubosc izolacji.\n");
        printf("Grubosc izolacji [cm] = ");
        scanf("%lf", &Z.d_isolation);
        if (Z.d_isolation < 0)
        {
            printf("Err : Wartosc nie moze byc ujemna.\n");
            return 0;
        }
        Z.d_isolation /= 100;
        result = find_q(Z);
        break;
    }
    default:
        printf("Skoro zadna cie nie interesuje, po co odpalasz program ? \n");
        return 0;
    }
    printf("=================================================\n");
    if (w == 1)
    {
        if (result > 0)
            printf("               Wynik = %.2lf[cm]                \n", result * 100);
        else
        {
            if (Z.q <= (Z.u_window * Z.s_window * Z.dt))
                printf("Error : Zbyt mala moc pieca, by ogrzac taki dom.\n");
            else
                printf("Nie potrzeba zakladac izolacji - moc pieca jest wystarczająca żeby ogrzewać dom.\n");
        }
    }
    if (w == 2)
    {
        if (result > 0)
            printf("               Wynik = %.2lf[W]                \n", result);
        else
            printf("Error : Something went wrong.\n");
    }
    printf("=================================================\n");
    printf("        Przez okna ucieka: %.2lf[W]\n", Z.u_window * Z.s_window * Z.dt);
    printf("=================================================\n");
    return 0;
}
