// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZRESOURCESMANAGER_H_INCLUDED__
#define __FZRESOURCESMANAGER_H_INCLUDED__
/*
 * FORZE ENGINE: http://forzefield.com
 *
 * Copyright (c) 2011-2012 FORZEFIELD Studios S.L.
 * Copyright (c) 2012 Manuel Martínez-Almeida
 * Copyright (c) 2008-2010 Ricardo Quesada
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/**
 @author Manuel Martínez-Almeida
 */

#include "FZTypes.h"
#include "FZAllocator.h"
#include "FZSelectors.h"


namespace FORZE {
    
#define FZRULE_MAXSIZE 8
#define FZRULE_NU 6

    class ResourcesManager : public SELProtocol
    {
    private:
        static ResourcesManager* p_instance;

        struct {
            char flag[FZRULE_MAXSIZE];
            fzUInt factor;
        } m_rules[FZRULE_NU];
        
        fzUInt m_nuRules;
        char *p_resourcesPath;

        void _generateAbsolutePath(const char *filename, const char *suffix, char *absolutePath) const;
        
        
    protected:
        ResourcesManager();
        ResourcesManager(const ResourcesManager& );
        ResourcesManager &operator = (const ResourcesManager& );
        
        ~ResourcesManager();
        void setupDefaultRules();
        
        
    public:
        //! Gets and allocates the singleton.
        static ResourcesManager& Instance();
        
        void generateAbsolutePath(const char *filename, fzUInt factor, char *absolutePath) const;
        
        //! Low level method to get the absolute resource path.
        bool getPath(const char *filename, fzUInt priority, char *absolutePath, fzUInt *factor) const;
        
        
        //! Adding new rules, you can load specified files for each platform version.
        void addRule(const char *device, const char *prefix, fzUInt factor = 1);
        
        
        //! High level method to load a file.
        //! @param factor. Returns the scaling factor of the file.
        fzBuffer loadResource(const char *filename, fzUInt *factor) const;
        
        
        //! High level method to load a file without scaling factor.
        fzBuffer loadResource(const char *filename) const;
        
        void checkFile(const char* file) const;
    };
}
#endif
