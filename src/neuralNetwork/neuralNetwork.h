typedef struct Neural Neural;
struct Neural
{
  double computedValue;
  double sumedValue;
};
typedef struct Layer Layer;
struct Layer
{
  unsigned numberUnits;
  Neural *Units;
  double **weights;
};

double computeSum(double output, double weight);
double computeOutput(double sumedResult);
void initializeNeural(Neural *Neural);
void initializeLayer(Layer *Layer, unsigned numberUnits, unsigned numberLinks);
void freeLayer(Layer *Layer);
void freeNeural(Neural *neural);
