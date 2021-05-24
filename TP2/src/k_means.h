double somme_pour_moy(double c_min, int c_max, int * histo);
double somme_pixel(double c_min, int c_max, int * histo);
double calcul_s(double inf, double sup, int * histo);
void threshold(Image<uint8_t> image, double * seuils, const char * nom, int part);