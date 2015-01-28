// Robin Radloff
// Purpose: Convert stereo WAVE to mono WAVE with normalized volume
// Can read 8 bit or 16 bit

#include <fstream>
#include <vector>
using namespace std;

enum Type {
  EIGHT,
  SIXTEEN
};

class WaveFile {
public:
  WaveFile(char * file_name)
  {
    ReadFile(file_name);
  }

private:
  short * mData;
  vector<short> mData2;
  unsigned mSize;
  Type type;


  void ReadFile(char * file_name)
  {
    fstream in(file_name, ios_base::in | ios_base::binary);
    char header[44];
    in.read(header, 44);
    mSize = *reinterpret_cast<unsigned*>(header + 40);
    mData = new short[mSize / 2];
    in.read(reinterpret_cast<char*>(mData), mSize);

    mData2.resize(mSize / 2);
    memcpy(&mData2[0], mData, mSize);
  }

  void ConvertToMono()
  {
    // Add left and rights together
  }

  void ConvertToVoltage()
  {
    // Subtract 128 if 8 bit
  }

  void Normalize()
  {
    // Find DC offset (average of values), remove offset
  }

  void ScaleToMaxVolume()
  {
    // Find target max
    // Find current max
    // Scale factor m
    // Multiply all by m
  }

  void ConvertTo8Bit()
  {
    // Add 128 if 8 bit
  }
};


int main ()
{
  WaveFile sound("Stereo8-11025-1.wav");
  //WaveFile sound("to_mono.wav");
  // Read in file do stuff I dunno
}