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
  unsigned numberLinks;
  Neural *Units;
  double **weights;
};

//Compute the sum of each neuron on Layer1 to each neuron on Layer2
void computeSum(Layer *Layer1, Layer *Layer2);
double sigmoid(double x);
//Number links <=> view of the layer view, not of eu each neuron
void initializeLayer(Layer *Layer, unsigned numberUnits, unsigned numberLinks);
void freeLayer(Layer *Layer);
