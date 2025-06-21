#pragma once

// ==================== 新增此行，解决所有问题的关键 ====================
#include "../../include/PluginInterface.h"
#include <string> // 包含 <string> 以使用 std::wstring
// ====================================================================

class CHardwareMonitorItem :
    public IPluginItem
{
public:
    // 原有构造函数
    CHardwareMonitorItem(const std::wstring& identifyer, const std::wstring& item_name, const std::wstring& lable_text);
    // 新增的构造函数，用于支持图形显示
    CHardwareMonitorItem(const std::wstring& identifyer, const std::wstring& item_name, const std::wstring& lable_text, bool is_graph, GraphType graph_mode);
    // 析构函数
    ~CHardwareMonitorItem();

    // 实现继承自 IPluginItem 的虚函数
    virtual const wchar_t* GetItemName() const override;
    virtual const wchar_t* GetItemLableText() const override;
    virtual const wchar_t* GetItemValueText() const override;
    virtual int GetItemWidth() const override;

    // 这是此类特有的函数 (不在 IPluginItem 中)
    const wchar_t* GetItemValueTip() const;

    // 这也是此类特有的函数
    void UpdateValue();

private:
    std::wstring m_identifyer;
    std::wstring m_item_name;
    std::wstring m_lable_text;
    float m_value{};
};
