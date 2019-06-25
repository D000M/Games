/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TextureManager.h
 * Author: default
 *
 * Created on June 25, 2019, 12:22 PM
 */

#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SFML/Graphics/Texture.hpp>

#include "ResourceManager.h"


class TextureManager : public ResourceManager<TextureManager, sf::Texture> {
    public:
        TextureManager() 
            : ResourceManager("textures.cfg") {} 
            
    /**
     * Override Resource Manager load() method
     * @param lPath std::string path to the textures.
     * @return created texture.
     */
    sf::Texture* load(const std::string& lPath) {
        sf::Texture* texture = new sf::Texture();
        if(!texture->loadFromFile(lPath)) {
            delete texture;
            texture = nullptr;
            std::cerr << "! Failed to load Texture: " << lPath << std::endl;
        }
        return texture;
    }
};

#endif /* TEXTUREMANAGER_H */

