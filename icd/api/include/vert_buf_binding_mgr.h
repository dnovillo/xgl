/*
 ***********************************************************************************************************************
 *
 *  Copyright (c) 2014-2018 Advanced Micro Devices, Inc. All Rights Reserved.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *
 **********************************************************************************************************************/
/**
 **************************************************************************************************
 * @file  vert_buf_binding_mgr.h
 * @brief Manages vertex buffer binding state while building command buffers
 **************************************************************************************************
 */

#ifndef __VERT_BUF_BINDING_MGR_H__
#define __VERT_BUF_BINDING_MGR_H__

#pragma once

#include "include/vk_graphics_pipeline.h"

// Forward declare PAL classes used in this file
namespace Pal
{

class ICmdBuffer;
class IGpuMemory;

};

namespace vk
{

class Buffer;
class CmdBuffer;
class GraphicsPipeline;
class Queue;

// =====================================================================================================================
// This is the vertex buffer binding manager class.  This class is owned by the CmdBuffer class.
//
// During command buffer building, it manages the state necessary to build and update the internal vertex buffer binding
// tables.  It ensures that VB SRDs are updated correctly when BindVertexBuffer is called, and when a pipeline change
// occurs it ensures that the internal vertex buffer table is rebound to the correct user data registers.
class VertBufBindingMgr
{
public:
    static constexpr Pal::uint16 VertexBufferTableId = 0;

    VertBufBindingMgr(Device* pDevice);
    ~VertBufBindingMgr();

    static size_t GetMaxVertBufTableDwSize(const PhysicalDevice* pPhysDevice);
    static size_t GetSize(const Device* pDevice);

    Pal::Result Initialize(void* pVbMem);
    void Reset();

    void BindVertexBuffers(
        CmdBuffer*          pCmdBuf,
        uint32_t            firstBinding,
        uint32_t            bindingCount,
        const VkBuffer*     pBuffers,
        const VkDeviceSize* pOffsets);

    void GraphicsPipelineChanged(CmdBuffer* pCmdBuf, const GraphicsPipeline* pPipeline);

private:

    uint32_t            m_vbSrdDwSize;                               // Size of a VB SRD in bytes
    Pal::BufferViewInfo m_bindings[MaxPalDevices][MaxVertexBuffers]; // VB bindings in source non-SRD form
    uint32_t*           m_pVbTblSysMem;                              // VB bindings in SRD form in system memory
    Device*             m_pDevice;                                   // Device pointer
    uint32_t            m_bindingTableSize;                          // Current size of the active VB table in slots

    PAL_DISALLOW_COPY_AND_ASSIGN(VertBufBindingMgr);
};

}

#endif /* __VERT_BUF_BINDING_MGR_H__ */
