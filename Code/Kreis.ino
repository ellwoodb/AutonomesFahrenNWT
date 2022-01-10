void kreis(int radius, int geschwindigkeit, int breiteDesAutos)
{
    float pi = 3.14159;
    int u = 2 * pi * radius;
    int hBreite = breiteDesAutos / 2;

    int ui = 2 * pi * (radius - hBreite);
    int ua = 2 * pi * (radius + hBreite);

    int t = 2 * pi / geschwindigkeit;

    int vi = ui / t;
    int va = ua / t;
}