/** ========================= **
 *  Auteur: Mathieu Gardette
 *  Promotion INFRES 10
 ** ========================= **/

#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>

#include "HAlgo.hpp"

#define DEBUG false

using namespace std;
using namespace Hungarian;

class Cell {
  protected :
    int index;
    int value;
  public :
    int getIndex() {return index;}
    int getValue() {return value;}
    void setValue(int newValue) {value = newValue;}
    void setIndex(int newIndex) {index = newIndex;}
};

vector<int> detectDoublons (vector< vector<Cell> > matrix) {
  vector <int> returned;
  for (int a = 0; a<(matrix.size()); a++) {
    int varToTest = a;
    int b = a;
    bool continuing = true;

    while ( (b < matrix[a].size() - a) && continuing )  {
      if (matrix[a][varToTest].getIndex() == matrix[a][b].getIndex()) {
        returned.push_back(matrix[a][varToTest].getIndex());
        continuing = false;
      }
      b++;
    }

    if  (returned.size() != a+1) {returned.push_back(-1);}
  }

  return returned;
}

bool cellCompare (Cell i,Cell j) { return (i.getValue() > j.getValue()); }


int somme(vector<vector<int>> mat, vector<int> tab) {
	int s = 0;
  for(size_t i=0; i<tab.size(); i++) {
    s += mat.at(i).at(tab.at(i));
  }
	return s;
}

vector<int> bruteforce(vector<vector<int>> mat, vector<int> tab, int l, int r) {
	vector<int> zmax;
	vector<int> zR;
	int vR;
	int vmax = 0;

  if(l==r) {
		return tab;
	} else {
    for(int i=l; i<r; i++) {  
			iter_swap(tab.begin() + l, tab.begin() + i);
      zR = bruteforce(mat, tab, l+1, r);
			vR = somme(mat, zR);
			if(vR > vmax) {
				zmax = zR;
				vmax = vR;
			}
      iter_swap(tab.begin() + l, tab.begin() + i);
		}

		return zmax;
	}
}

//--- MAIN ---
int main (int argc, char* argv[]) {

  int size;
  vector<vector<Cell>> sorted ;
  string filepath = "./aff" + string(argv[1]) + ".txt";
  FILE *file;
  file = fopen(filepath.c_str(),"r+");

  fscanf(file, "%d", &size);

  // Créer un tableau de "size" par "size" éléments de valeur -1
  vector<int> tab;
  vector<vector<int>> arr (size, vector<int>(size));

  for (int i = 0; i<size; i++) {
    for (int j = 0; j <size; j++){
      fscanf(file, "%d", &arr[i][j]);
    }
    tab.push_back(i);
  }


  // recherche par bruteforce
  tab = bruteforce(arr, tab, 0, size - 1);
  for (int a = 0; a < size; a++) {
    cout << tab.at(a) << " ";
  }
  cout << "\n";
  cout << somme(arr, tab) << "\n";

  /* tentatice de recherche en brute force améliorée
  //Remonte un vector rerésentant les colonnes d'une ligne de la matrice après l'avoir trié dans un vector de vector représentant la collection des lignes
  //Les valeurs de la première colonne sont donc les maximums
  for (size_t i=0; i<arr.size(); i++){
    vector<Cell> line; // Chaque i est une ligne
    for (size_t a = 0; a<arr[i].size(); a++) {
      Cell item;
      item.setValue(arr[i][a]);
      item.setIndex(a);
      line.push_back(item);
    }
    sort(line.begin(), line.end(), cellCompare); 
    sorted.push_back(line);
  }

  for (size_t a = 0; a < sorted.size(); a++) {
    for (size_t b = 0; b < sorted[a].size(); b++) {
      printf("%4d(%d) ", sorted[a][b].getValue(), sorted[a][b].getIndex());
    }
    printf("\n");
  }
  */

  //Résolution optimale
  Result r = Solve(arr, MODE_MAXIMIZE_UTIL);

  int rS = 0;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if(r.assignment.at(i).at(j) == 1) {
        rS += arr.at(i).at(j);
      }
    }
  }

  cout << rS;

  puts("\n");
  fclose(file); 
  return 0;
}