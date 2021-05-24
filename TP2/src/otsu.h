double somme_pour_moy(double c_min, int c_max, int * histo);
double somme_pixel(double c_min, int c_max, int * histo);
double otsu_seuil(double seuil, double n, int * histo);
void threshold(Image<uint8_t> image, double seuil, const char * nom);