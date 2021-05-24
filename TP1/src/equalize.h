double search_min_img(int * histo);
double search_max_img(int * histo);
void equalize_img(Image<uint8_t> image, double Imin, double Imax, const char* nom, int * histo);
double somme(double Imin, int offset, int * histo);