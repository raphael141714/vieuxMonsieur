/** ========================= **
 *  Auteur: Mathieu Gardette
 *  Promotion INFRES 10
 ** ========================= **/

#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <algorithm>
#include <vector>

#define DEBUG 

using namespace std;

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

bool myfunction (Cell i,Cell j) { return (i.getValue() > j.getValue()); }

//--- MAIN ---
int main (int argc, char* argv[]){

  int size;
  vector<vector<Cell> > sorted ;
  FILE *file;
  file = fopen("./aff1.txt","r+");

  fscanf(file, "%d", &size);

  // Créer un tableau de "size" par "size" éléments de valeur -1
  vector<vector<int> > arr (size, vector<int>(size, -1));

  for (int i = 0; i<size; i++){
    for (int j = 0; j <size; j++){
      fscanf(file, "%d", &arr[i][j]);
    }
  }

  //Remonte un vector rerésentant les colonnes d'une ligne de la matrice après l'avoir trié dans un vector de vector représentant la collection des lignes
  //Les valeurs de la première colonne sont donc les maximums
  for (int i=0; i<arr.size(); i++){

    vector<Cell> line; // Chaque i est une ligne
    for (int a = 0; a<arr[i].size(); a++) {
      Cell item;
      item.setValue(arr[i][a]);
      item.setIndex(a);

      line.push_back(item);
    }

    sort(line.begin(), line.end(), myfunction); 
    sorted.push_back(line);
  }

  for (int a = 0; a < sorted.size(); a++) {
    for (int b = 0; b < sorted[a].size(); b++) {
      printf("%4d(%d) ", sorted[a][b].getValue(), sorted[a][b].getIndex());
    }
    printf("\n");
  }

  puts("\n");
  fclose(file); 
  return 0;
}