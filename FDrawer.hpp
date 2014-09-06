#ifndef FDRAWER_HPP
#define FDRAWER_HPP
#include <vector>
#include <valarray>

class FDrawer {

public:
  virtual void Draw(const std::vector<std::valarray<double> >& array, int xRowLen) = 0;

};

class FDrawerOpenGL1 : public FDrawer {
public:
  void Draw(const std::vector<std::valarray<double> > &array, int xRowLen);
};

#endif // FDRAWER_HPP
