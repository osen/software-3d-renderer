#include "Model.h"
#include "Exception.h"
#include "Part.h"
#include "MaterialGroup.h"
#include "Platform.h"
#include "Resources.h"
#include "Texture.h"

#include <qsoft/qsoft.h>

#include <fstream>
#include <iostream>

struct Material
{
  std::string name;
  std::shared_ptr<Texture> texture;
};

void Model::splitStringWhitespace(std::string& input, std::vector<std::string>& output)
{
  std::string curr;

  output.clear();

  for(size_t i = 0; i < input.length(); i++)
  {
    if(input.at(i) == ' ' ||
      input.at(i) == '\r' ||
      input.at(i) == '\n' ||
      input.at(i) == '\t')
    {
      if(curr.length() > 0)
      {
        output.push_back(curr);
        curr = "";
      }
    }
    else
    {
      curr += input.at(i);
    }
  }

  if(curr.length() > 0)
  {
    output.push_back(curr);
  }
}

void Model::splitString(std::string& input, char splitter, std::vector<std::string>& output)
{
  std::string curr;

  output.clear();

  for(size_t i = 0; i < input.length(); i++)
  {
    if(input.at(i) == splitter)
    {
      output.push_back(curr);
      curr = "";
    }
    else
    {
      curr += input.at(i);
    }
  }

  if(curr.length() > 0)
  {
    output.push_back(curr);
  }
}

void Model::onLoad(std::string path)
{
  std::ifstream file(std::string(path + ".obj").c_str());

  if(!file.is_open())
  {
    throw Exception("Failed to open model '" + path + "'");
  }

  std::string line;
  std::vector<std::string> splitLine;
  std::vector<qsoft::Vector3> positions;
  std::vector<qsoft::Vector2> texCoords;
  std::vector<qsoft::Vector3> normals;
  std::vector<std::shared_ptr<Material> > materials;

  std::shared_ptr<Part> part;
  std::shared_ptr<MaterialGroup> mg;
  std::shared_ptr<Material> material;

  while(!file.eof())
  {
    std::getline(file, line);
    if(line.length() < 1) continue;
    splitStringWhitespace(line, splitLine);
    if(splitLine.size() < 1) continue;

    if(splitLine.at(0) == "v")
    {
      positions.push_back(qsoft::Vector3(
        -atof(splitLine.at(1).c_str()),
        atof(splitLine.at(2).c_str()),
        atof(splitLine.at(3).c_str())));
    }
    else if(splitLine.at(0) == "vt")
    {
      texCoords.push_back(qsoft::Vector2(
        atof(splitLine.at(1).c_str()),
        atof(splitLine.at(2).c_str())));
    }
    else if(splitLine.at(0) == "vn")
    {
      normals.push_back(qsoft::Vector3(
        atof(splitLine.at(1).c_str()),
        atof(splitLine.at(2).c_str()),
        atof(splitLine.at(3).c_str())));
    }
    else if(splitLine.at(0) == "f")
    {
      if(!part)
      {
        part = std::make_shared<Part>();
        part->name = "Default";
        parts.push_back(part);
      }

      if(!mg)
      {
        mg = std::make_shared<MaterialGroup>();
        mg->setTexture(material->texture);
        part->addMaterialGroup(mg);
      }

      if(positions.size() < 1) throw Exception("Model does not specify any vertex positions");
      if(texCoords.size() < 1) throw Exception("Model does not specify any texture coordinates");
      std::vector<std::string> subsplit;

      qsoft::Face f;
      splitString(splitLine.at(1), '/', subsplit);
      f.a.position = positions.at(atoi(subsplit.at(0).c_str()) - 1);
      f.a.texCoord = texCoords.at(atoi(subsplit.at(1).c_str()) - 1);
      //f.a.normal = normals.at(atoi(subsplit.at(2).c_str()) - 1);
      splitString(splitLine.at(2), '/', subsplit);
      f.b.position = positions.at(atoi(subsplit.at(0).c_str()) - 1);
      f.b.texCoord = texCoords.at(atoi(subsplit.at(1).c_str()) - 1);
      //f.b.normal = normals.at(atoi(subsplit.at(2).c_str()) - 1);
      splitString(splitLine.at(3), '/', subsplit);
      f.c.position = positions.at(atoi(subsplit.at(0).c_str()) - 1);
      f.c.texCoord = texCoords.at(atoi(subsplit.at(1).c_str()) - 1);
      //f.c.normal = normals.at(atoi(subsplit.at(2).c_str()) - 1);
      mg->addFace(f);
      faces.push_back(f);
      if(splitLine.size() < 5) continue;

      f = qsoft::Face();
      splitString(splitLine.at(3), '/', subsplit);
      f.a.position = positions.at(atoi(subsplit.at(0).c_str()) - 1);
      f.a.texCoord = texCoords.at(atoi(subsplit.at(1).c_str()) - 1);
      //f.a.normal = normals.at(atoi(subsplit.at(2).c_str()) - 1);
      splitString(splitLine.at(4), '/', subsplit);
      f.b.position = positions.at(atoi(subsplit.at(0).c_str()) - 1);
      f.b.texCoord = texCoords.at(atoi(subsplit.at(1).c_str()) - 1);
      //f.b.normal = normals.at(atoi(subsplit.at(2).c_str()) - 1);
      splitString(splitLine.at(1), '/', subsplit);
      f.c.position = positions.at(atoi(subsplit.at(0).c_str()) - 1);
      f.c.texCoord = texCoords.at(atoi(subsplit.at(1).c_str()) - 1);
      //f.c.normal = normals.at(atoi(subsplit.at(2).c_str()) - 1);
      mg->addFace(f);
      faces.push_back(f);
    }
    else if(splitLine.at(0) == "usemtl")
    {
      material.reset();

      for(std::vector<std::shared_ptr<Material> >::iterator mit = materials.begin();
        mit != materials.end(); mit++)
      {
        if((*mit)->name == splitLine.at(1))
        {
          material = *mit;
          break;
        }
      }

      if(!material)
      {
        throw Exception("Invalid material '" + splitLine.at(1) + "' specified");
      }

      if(!part)
      {
        part = std::make_shared<Part>();
        part->name = "Default";
        parts.push_back(part);
      }

      mg = std::make_shared<MaterialGroup>();
      mg->setTexture(material->texture);
      part->addMaterialGroup(mg);
    }
    else if(splitLine.at(0) == "o" || splitLine.at(0) == "g")
    {
      part = std::make_shared<Part>();
      part->name = splitLine.at(1);
      parts.push_back(part);
      mg.reset();
    }
    else if(splitLine.at(0) == "mtllib")
    {
      std::string dir = path;

      for(size_t i = 0; i < dir.size(); i++)
      {
        if(dir.at(i) == '\\') dir.at(i) = '/';
      }

      size_t pos = dir.rfind('/');

      if(pos != std::string::npos)
      {
        dir.erase(pos);
      }
      else
      {
        dir = "";
      }

      processMtl(dir + "/" + splitLine.at(1), materials);
    }
  }
}

void Model::processMtl(std::string path,
  std::vector<std::shared_ptr<Material> >& materials)
{
  std::ifstream file(std::string(path).c_str());

  if(!file.is_open())
  {
    throw Exception("Failed to open material file '" + path + "'");
  }

  std::string dir = path;

  for(size_t i = 0; i < dir.size(); i++)
  {
    if(dir.at(i) == '\\') dir.at(i) = '/';
  }

  size_t pos = dir.rfind('/');

  if(pos != std::string::npos)
  {
    dir.erase(pos);
  }
  else
  {
    dir = "";
  }

  std::string line;
  std::vector<std::string> splitLine;
  std::shared_ptr<Material> material;

  while(!file.eof())
  {
    std::getline(file, line);
    if(line.length() < 1) continue;
    splitStringWhitespace(line, splitLine);
    if(splitLine.size() < 1) continue;

    if(splitLine.at(0) == "newmtl")
    {
      material = std::make_shared<Material>();
      materials.push_back(material);
      material->name = splitLine.at(1);
      material->texture = getPlatform()->getResources()->getDefaultTexture();
    }
    else if(splitLine.at(0) == "map_Kd")
    {
      std::string file = dir + "/" + splitLine.at(1);

      size_t pos = file.rfind(".");

      if(pos != std::string::npos)
      {
        file.erase(pos);
      }

      material->texture =
        getPlatform()->getResources()->load<Texture>(file);
    }
  }
}
