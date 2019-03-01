/*++
Copyright (c) Microsoft Corporation

Module Name:
- utils.hpp

Abstract:
- Helpful cross-lib utilities

Author(s):
- Mike Griese (migrie) 12-Jun-218
--*/

namespace Microsoft::Console::Utils
{
    bool IsValidHandle(const HANDLE handle) noexcept;

    void InitializeCampbellColorTable(gsl::span<COLORREF>& table);
    void Initialize256ColorTable(gsl::span<COLORREF>& table);
    void SetColorTableAlpha(gsl::span<COLORREF>& table, const BYTE newAlpha);
}