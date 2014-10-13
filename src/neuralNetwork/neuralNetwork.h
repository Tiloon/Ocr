typedef struct Neural Neural;
struct Neural
{
  long double computedValue;
  long double sumedValue;
  long double bias;
};
typedef struct Layer Layer;
struct Layer
{
  unsigned numberUnits;
  unsigned numberLinks;
  Neural *Units;
  long double **weights;
};

//Compute the sum of each neuron on Layer1 to each neuron on Layer2
//And also call sigmoid function and update each neuron value
void computeSum(Layer *Layer1, Layer *Layer2);
long double sigmoid(long double x);
//Number links <=> view of the layer view, not of eu each neuron
void initializeLayer(Layer *Layer, unsigned numberUnits, unsigned numberLinks);
void freeLayer(Layer *Layer);
void computeData(Layer *Input, Layer *Hidden, Layer *Output);
