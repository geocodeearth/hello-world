#include <iostream>
#include "ogrsf_frmts.h"

void printRing(OGRLinearRing *ring)
{
  for (int p = 0; p < ring->getNumPoints(); p++)
  {
    OGRPoint *point = new OGRPoint();
    ring->getPoint(p, point);

    printf("[%f, %f]", point->getX(), point->getY());
  }
}

int main()
{
  GDALAllRegister();

  GDALDataset *poDS;
  poDS = (GDALDataset*) GDALOpenEx("data/example.geojson", GDAL_OF_VECTOR, NULL, NULL, NULL);
  if( poDS == NULL )
  {
    printf("Open failed.\n");
    exit(1);
  }

  OGRLayer  *poLayer;
  poLayer = poDS->GetLayer(0);
  poDS->ResetReading();

  OGRFeature *poFeature;

  while((poFeature = poLayer->GetNextFeature()) != NULL)
  {
    OGRGeometry *poGeometry = poFeature->GetGeometryRef();

    // poGeometry->getGeometryType() == wkbMultiPolygon
    OGRMultiPolygon *poMultiPoly = poGeometry->toMultiPolygon();

    for (int i = 0; i < poMultiPoly->getNumGeometries(); i++)
    {
      OGRGeometry *poChildGeometry = poMultiPoly->getGeometryRef(i);
      OGRPolygon *poPolygon = poChildGeometry->toPolygon();

      printRing(poPolygon->getExteriorRing());
      for (int r = 0; r < poPolygon->getNumInteriorRings(); r++)
      {
        printRing(poPolygon->getInteriorRing(r));
      }
    }

    OGRFeature::DestroyFeature(poFeature);
  }

  GDALClose(poDS);
}
