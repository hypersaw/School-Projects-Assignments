#include "reader.h"

int NodeCounter = 0;
int faceCounter = 0;


/* Opens the XML file based on the entire pathname "fileName" */

void openFile(const char * fileName) {



  xmlNode *currPtr;
  xmlNode *currNode;

  doc = xmlReadFile(fileName, NULL, 0);

  head = xmlDocGetRootElement(doc);



  if(doc == NULL){
    printf("error: could not parse file %s\n", fileName);
  }

  printf("Right at %s \n",head->name);

  if (head->type == XML_ELEMENT_NODE && strcmp((const char*) head->name, "Project2") == 0) {
    for (currPtr = head->children; currPtr != NULL; currPtr = currPtr->next) {

      if (currPtr->type == XML_ELEMENT_NODE && strcmp((const char*) currPtr->name, "Wireframe") == 0) {
	for (currNode = currPtr->children; currNode; currNode = currNode->next) {
	  if(currNode->type == XML_ELEMENT_NODE && strcmp((const char*) currNode->name,"NumPoints") == 0) {
	    nodeCount = atoi((char*) currNode->children->content);
	    printf("nodeCount %d \n",nodeCount);
	  }
	}
      } else if (currPtr->type == XML_ELEMENT_NODE && strcmp((const char*) currPtr->name, "LineDraw") == 0) {
	for (currNode = currPtr->children; currNode; currNode = currNode->next) {
	  if(currNode->type == XML_ELEMENT_NODE && strcmp((const char*) currNode->name,"NumPoints") == 0) {
	    faceCount = atoi((char*) currNode->children->content);
	    printf("faceCount %d \n",faceCount);
	  }
	}
      }

    }
  }

  if (nodeCount > 0) {
    nodeList = (Node*)malloc(sizeof(struct Node) * nodeCount);
    printf("Node size initialized to %d value \n",nodeCount);
  }else {
    printf("Warning: node size has not been initialized \n");
  }

  if (faceCount > 0 ) {
    faceList = (Face*)malloc(sizeof(struct Face) * faceCount);
    printf("face points initialized to %d \n",faceCount);
  }else {
    printf("Warning: face size has not been initialized");
  }


}

void parseDatabase() {


   xmlNode *currPtr;
   xmlNode *currNode;


    if (doc == NULL) {
      printf("error: xml pointer is NULL ");
      return;
    }

    if (head->type == XML_ELEMENT_NODE && strcmp((const char*) head->name, "Project2") == 0) {
        for (currPtr = head->children; currPtr; currPtr = currPtr->next) {


	  // Reading cononical volume paramaters, umin,umax,vmin,vmax,FrontPlane,BackPlane
	  parseCononicalVolume(currPtr);

      // Reads VPN,VUP,VRP,PRP
	  parseVRC(currPtr);



          // Wireframe tag
	  if (currPtr->type == XML_ELEMENT_NODE && strcmp((const char*) currPtr->name, "Wireframe") == 0) {
	    for (currNode = currPtr->children; currNode; currNode = currNode->next) {

               parseNode(currNode,8);                // Starts with the tag "Coordinates3D" to read the Point data
               parseColor(currNode,8);               // Start with "OutlineColor" or "FillColor" to read the Color data
               parseLineConnectivity(currNode,8);    // Starts with "LineConnectivity to read the Connectivity data
	    }

	  }

          //Sphere
	  else if (currPtr->type == XML_ELEMENT_NODE && strcmp((const char*) currPtr->name, "Sphere") == 0) {
	    for (currNode = currPtr->children; currNode; currNode = currNode->next) {
                parseColor(currNode,6);
                parseRadius(currNode,6);  // Reads the "Radius" value
                parseCenter(currNode,6);  // Starts with the "Center" value to parse the point

	    }

	  }

          //Cylinder
	  else if (currPtr->type == XML_ELEMENT_NODE && strcmp((const char*) currPtr->name, "Cylinder") == 0) {
	    for (currNode = currPtr->children; currNode; currNode = currNode->next) {

                parseColor(currNode,10);
                parseRadius(currNode,10);
	        parseCenter(currNode,10);
                parseHeight(currNode,10);

	    }

	  }

	  // LineDraw
	  else if (currPtr->type == XML_ELEMENT_NODE && strcmp((const char*) currPtr->name, "LineDraw") == 0) {
	    for (currNode = currPtr->children; currNode; currNode = currNode->next) {
	      parseColor(currNode,9);
	      parseNode(currNode,9);
	    }
	  }

	}
    }

    xmlFreeDoc(doc);
    xmlCleanupParser();
   

}

void printDatabase() {
  
  int i = 0;
  Connectivity *ptr = NULL;
  if (nodeCount > 0) {
    printf("------ Node Points -----------\n");
    for (i = 0; i < nodeCount; i++) {

      printf("Point %d :  { %f, %f,%f } \n ",i+1, nodeList[i].point.x,nodeList[i].point.y,nodeList[i].point.z);
    }
  }

  if (faceCount > 0) {
    printf("------ Face Points -----------\n");
    for (i = 0; i < faceCount; i++) {

      printf("Point %d :  { %f, %f,%f } \n ",i+1, faceList[i].point.x,faceList[i].point.y,faceList[i].point.z);
    }
  }

  i = 1;
  for (ptr = headEdgePtr; ptr != NULL; ptr = ptr->next,i++) {
      printf("Line %d: %d -> %d \n",i,ptr->id1,ptr->id2);
  }

  // volume
  printf("----------- Volume PARAMATERS --------------\n\n");
  printf("umin: %f  umax: %f vmin: %f vmax: %f \n",volume.uMin,volume.uMax,volume.vMin,volume.vMax);
  printf("front plane: %f back plane %f \n",volume.zMin,volume.zMax);

  printf("---------- VRC PARAMATERS ------------\n\n");
  printf("vrp: %f,%f,%f  \n",vrc.vrp.x,vrc.vrp.y,vrc.vrp.z);
  printf("vpn: %f,%f,%f  \n",vrc.vpn.x,vrc.vpn.y,vrc.vpn.z);
  printf("vup: %f,%f,%f  \n",vrc.vup.x,vrc.vup.y,vrc.vup.z);
  printf("prp: %f,%f,%f  \n",vrc.prp.x,vrc.prp.y,vrc.prp.z);


  //Sphere
  printf("--------------SPHERE--------------------\n\n");
  printf("Center: %f,%f,%f \n",sphere.center.x,sphere.center.y,sphere.center.z);
  printf("Color:  %f,%f,%f \n",sphere.color.r,sphere.color.g,sphere.color.b);
  printf("Radius:  %f \n",sphere.radius);

  //Cylinder
  printf("--------------CYLINDER--------------------\n\n");
  printf("Center: %f,%f,%f \n",cylinder.center.x,cylinder.center.y,cylinder.center.z);
  printf("Color:  %f,%f,%f \n",cylinder.color.r,cylinder.color.g,cylinder.color.b);
  printf("Radius:  %f \n",cylinder.radius);
  printf("Height:  %f \n",cylinder.height);

}

void parseCenter(xmlNode *node, int type) {
  xmlNode *currNode;

  if (node->type == XML_ELEMENT_NODE && strcmp((const char*) node->name,"Center") == 0) {
    for(currNode = node->children; currNode != NULL; currNode = currNode->next) {
      parsePoints(currNode,type);
    }
  }
 
}



void parseCononicalVolume(xmlNode *ptr) {
    
  	  if (ptr->type == XML_ELEMENT_NODE && strcmp((const char*) ptr->name,"umin") == 0) {
	    volume.uMin = atof((char*) ptr->children->content);
	  } else if (ptr->type == XML_ELEMENT_NODE && strcmp((const char*) ptr->name,"umax") == 0 ) {
	    volume.uMax = atof((char*) ptr->children->content);
	  } else if (ptr->type == XML_ELEMENT_NODE && strcmp((const char*) ptr->name,"vmin") == 0) {
	    volume.vMin = atof((char*) ptr->children->content);
	  } else if (ptr->type == XML_ELEMENT_NODE && strcmp((const char*) ptr->name,"vmax") == 0) {
	    volume.vMax = atof((char*) ptr->children->content);
	  }  else if (ptr->type == XML_ELEMENT_NODE && strcmp((const char*) ptr->name,"FrontPlane") == 0) {
	    volume.zMin = atof((char*) ptr->children->content);
	  }  else if (ptr->type == XML_ELEMENT_NODE && strcmp((const char*) ptr->name,"BackPlane") == 0) {
	    volume.zMax = atof((char*) ptr->children->content);
	  }
     
}

void parseVRC(xmlNode *ptr) {
    

    xmlNode *currNode = NULL;
  	  if (ptr->type == XML_ELEMENT_NODE && strcmp((const char*) ptr->name,"PRP") == 0) {
	      for (currNode = ptr->children; currNode; currNode = currNode->next)
		parsePoints(currNode,2);
              printf("PRP: %f,%f,%f \n",vrc.prp.x,vrc.prp.y,vrc.prp.z);
	  } else if (ptr->type == XML_ELEMENT_NODE && strcmp((const char*) ptr->name,"VPN") == 0 ) {
	    for (currNode = ptr->children; currNode; currNode = currNode->next)
	      parsePoints(currNode,0);
            printf("VPN: %f,%f,%f \n",vrc.vpn.x,vrc.vpn.y,vrc.vpn.z);
	  } else if (ptr->type == XML_ELEMENT_NODE && strcmp((const char*) ptr->name,"VUP") == 0) {
	    for (currNode = ptr->children; currNode; currNode = currNode->next)
	      parsePoints(currNode,1);
            printf("VUP: %f,%f,%f \n",vrc.vup.x,vrc.vup.y,vrc.vup.z);
	  } else if (ptr->type == XML_ELEMENT_NODE && strcmp((const char*) ptr->name,"VRP") == 0 ) {
	    for (currNode = ptr->children; currNode; currNode = currNode->next)
	      parsePoints(currNode,3);
            printf("VRP: %f,%f,%f \n",vrc.vrp.x,vrc.vrp.y,vrc.vrp.z);
          }
    
}


void parseNode(xmlNode *node, int type) {
    
    xmlNode *currPtr;
    NodeCounter = 0;
    if (strcmp((const char *) node->name,"Coordinates3D") != 0 ) return;

        if (node->type == XML_ELEMENT_NODE) {
            for (currPtr = node->children; currPtr;currPtr = currPtr->next) {
               if (type == 8) parsePoints(currPtr,8);
               if (type == 9) parsePoints(currPtr,9);
            }

        }


}

void parseLineConnectivity(xmlNode *node,int type) {
   
  int point1, point2;
  xmlNode *currPtr;
  if (strcmp((const char*) node->name,"LineConnectivity") != 0) return;

  for (currPtr = node->children; currPtr; currPtr = currPtr->next) {
      if (currPtr->type == XML_ELEMENT_NODE && strcmp((const char*) currPtr->name,"id") == 0){
	point1 = atoi((char*) currPtr->children->content);

      // Go to the next id
      currPtr = currPtr->next;
      if (currPtr == NULL || strcmp((const char*) currPtr->name,"id") != 0) {
	printf("Expected listing of id2 in lineConnectivity");
      }

      if (currPtr->type == XML_ELEMENT_NODE && strcmp((const char*) currPtr->name,"id") == 0)
	point2 = atoi((char*) currPtr->children->content);

      if (type == 8 ) {
            if (headEdgePtr == NULL) {
            headEdgePtr = (Connectivity*)malloc(sizeof(struct Connectivity));
            headEdgePtr->next = NULL;
            headEdgePtr->id1 = point1;
            headEdgePtr->id2 = point2;
            tailEdgePtr = headEdgePtr;
        }else {
            tailEdgePtr->next = (Connectivity*)malloc(sizeof(struct Connectivity));
            tailEdgePtr = tailEdgePtr->next;
            tailEdgePtr->id1 = point1;
            tailEdgePtr->id2 = point2;
            tailEdgePtr->next = NULL;
        }
     }
      }
  }
     
}



void parseRadius(xmlNode *node, int type) {
    
  float radius;
  int isEvaluated = 0;
  if (node->type == XML_ELEMENT_NODE && (isEvaluated==0)&& strcmp((const char*) node->name,"Radius") == 0) {
    radius = atof((char*) node->children->content);
    isEvaluated=1;
  }

  if (type == 10 && isEvaluated==1) {
    cylinder.radius = radius;
  } else if (type == 6&& isEvaluated==1) {
    sphere.radius = radius;
  }
    
}

void parseHeight(xmlNode *node, int type) {

  float height;
  int isEvaluated = 0;
  if (node->type == XML_ELEMENT_NODE && (isEvaluated==0)&& strcmp((const char*) node->name,"Height") == 0) {
    height = atof((char*) node->children->content);
    isEvaluated=1;
  }

  if (type == 10 && isEvaluated==1) {
    cylinder.height = height;
  }

}


void parseColor(xmlNode *node, int type) {
    
    float r = 0;
    float g = 0;
    float b = 0;
  xmlNode *currNode;
  xmlNode *color1Node;

  for (color1Node = node; color1Node; color1Node = color1Node->next){

  if (color1Node->type == XML_ELEMENT_NODE && strcmp((const char*) color1Node->name, "OutlineColor") == 0) {
    xmlNode *colorNode;
  //  printf("TAG NAME IS %s \n",colorNode->name);
    for (colorNode = color1Node->children; colorNode; colorNode = colorNode->next) {
        if (colorNode->type == XML_ELEMENT_NODE && strcmp((const char*) colorNode->name,"Color") == 0) {
         for (currNode = colorNode->children; currNode; currNode = currNode->next) {

	   if (currNode->type == XML_ELEMENT_NODE && strcmp((const char*) currNode->name,"Red") == 0) {
	       r = atof((char*) currNode->children->content);

	   }

	   if (currNode->type == XML_ELEMENT_NODE && strcmp((const char*) currNode->name,"Green") == 0) {
	    g = atof((char*) currNode->children->content);
	   }

	   if (currNode->type == XML_ELEMENT_NODE && strcmp((const char*) currNode->name,"Blue") == 0) {
	       b = atof((char*) currNode->children->content);
	   }

        }

      if (type == 10 ) {
	cylinder.color.r = r;
	cylinder.color.g = g;
	cylinder.color.b = b;
      }else if (type == 6 ) {
	sphere.color.r = r;
	sphere.color.g = g;
	sphere.color.b = b;
      }else if (type == 8 ) // WireFrame
      {
          nodeList[0].color.r  =r;
          nodeList[0].color.g  =g;
          nodeList[0].color.b  =b;
      }
      else if (type =9 )  //LineDraw
      {
          faceList[0].color.r = r;
          faceList[0].color.g = g;
          faceList[0].color.b = b;
      }
    }
  }
  }
  }
    

}


void parsePoints(xmlNode *node, int type) {
    
  float x,y,z = 0;
  xmlNode *currNode;
  xmlNode *tmpNode;


  if (strcmp((const char*) node->name,"Point") != 0) {
      return;
  }

 // printf("GOT TO HERE !!! \n");

    for (currNode = node->children; currNode; currNode = currNode->next) {
      if (currNode->type == XML_ELEMENT_NODE && strcmp((const char*) currNode->name, "x") == 0) {
	x = atof((char*) currNode->children->content);
     //   printf("x: %f \n",x);
      } else if (currNode->type == XML_ELEMENT_NODE && strcmp((const char*) currNode->name, "y") == 0) {
        y = atof((char*) currNode->children->content);
     //   printf("y: %f \n",y);
      } else if (currNode->type == XML_ELEMENT_NODE && strcmp((const char*) currNode->name, "z") == 0) {
	z = atof((char*) currNode->children->content);
     //   printf("z: %f \n",z);
      }
    }
      if (type == 0 ) {
      //VPN
	vrc.vpn.x = x;
	vrc.vpn.y = y;
	vrc.vpn.z = z;
      }else if (type == 1 ) {
     //VUP
	vrc.vup.x = x;
	vrc.vup.y = y;
	vrc.vup.z = z;
      }else if (type == 2)  {
     //PRP
	vrc.prp.x = x;
	vrc.prp.y = y;
	vrc.prp.z = z;
      }else if (type == 3 ) {
     //VRP
	vrc.vrp.x = x;
	vrc.vrp.y = y;
	vrc.vrp.z = z;
      }else if (type == 8 ) {
      //Wireframe
          if (NodeCounter >= nodeCount) {
              printf("Error reading past the point list for WIREFRAME");
              exit(0);
          }
	nodeList[NodeCounter].point.x = x;
	nodeList[NodeCounter].point.y = y;
	nodeList[NodeCounter].point.z = z;
   //     printf("%f %f %f \n",x,y,z);
	NodeCounter++;
      }else if (type == 9 ) {
     //LineDraw
          if(faceCounter >= faceCount) {
              printf("Error reading past the point list for LineDraw");
              exit(0);
          }
	faceList[faceCounter].point.x = x;
	faceList[faceCounter].point.y = y;
	faceList[faceCounter].point.z = z;
	faceCounter++;
      }else if (type == 6 ) {
        //Sphere
	sphere.center.x = x;
	sphere.center.y = y;
	sphere.center.z = z;
      }else if (type == 10 ) {
       //Cylinder
	cylinder.center.x = x;
	cylinder.center.y = y;
	cylinder.center.z = z;
      }

}
