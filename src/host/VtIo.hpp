// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#pragma once

#include "..\inc\VtIoModes.hpp"
#include "..\renderer\vt\vtrenderer.hpp"
#include "VtInputThread.hpp"
#include "PtySignalInputThread.hpp"

class ConsoleArguments;

namespace Microsoft::Console::VirtualTerminal
{
    class VtIo
    {
    public:
        VtIo();
        ~VtIo();

        [[nodiscard]] HRESULT Initialize(const ConsoleArguments* const pArgs);

        [[nodiscard]] HRESULT CreateAndStartSignalThread() noexcept;
        [[nodiscard]] HRESULT CreateIoHandlers() noexcept;

        bool IsUsingVt() const;

        [[nodiscard]] HRESULT StartIfNeeded();

        [[nodiscard]] static HRESULT ParseIoMode(const std::wstring& VtMode, _Out_ VtIoMode& ioMode);

        [[nodiscard]] HRESULT SuppressResizeRepaint();
        [[nodiscard]] HRESULT SetCursorPosition(const COORD coordCursor);

        void BeginResize();
        void EndResize();

    private:
        wil::shared_event _shutdownEvent;
        std::future<void> _shutdownWatchdog;

        // After CreateIoHandlers is called, these will be invalid.
        wil::unique_hfile _hInput;
        wil::unique_hfile _hOutput;
        // After CreateAndStartSignalThread is called, this will be invalid.
        wil::unique_hfile _hSignal;
        VtIoMode _IoMode;

        bool _initialized;
        bool _objectsCreated;

        bool _lookingForCursorPosition;

        std::unique_ptr<Microsoft::Console::Render::VtEngine> _pVtRenderEngine;
        std::unique_ptr<Microsoft::Console::VtInputThread> _pVtInputThread;
        std::unique_ptr<Microsoft::Console::PtySignalInputThread> _pPtySignalInputThread;

        [[nodiscard]] HRESULT _Initialize(const HANDLE InHandle, const HANDLE OutHandle, const std::wstring& VtMode, _In_opt_ const HANDLE SignalHandle);

        void _OnLastProcessExit();

#ifdef UNIT_TESTING
        bool _doNotTerminate;
        friend class VtIoTests;
#endif
    };
}
