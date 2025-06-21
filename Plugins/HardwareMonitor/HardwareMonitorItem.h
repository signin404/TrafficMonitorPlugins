#pragma once
#include "PluginInterface.h"
#include <string>
#include "CommonData.h"
// ==================== 新增此行，解决所有问题的关键 ====================
#include "../../include/PluginInterface.h"
// ====================================================================

namespace HardwareMonitor
{
    class CHardwareMonitorItem : public IPluginItem
    {
    public:
        CHardwareMonitorItem(const std::wstring& _identifier, const std::wstring& _item_name, const std::wstring& _label_text);
        CHardwareMonitorItem(const std::wstring& identifyer, const std::wstring& item_name, const std::wstring& lable_text, bool is_graph, GraphType graph_mode);

        ~CHardwareMonitorItem();
    virtual const wchar_t* GetItemName() const override;
    virtual const wchar_t* GetItemLableText() const override;
    virtual const wchar_t* GetItemValueText() const override;
    virtual const wchar_t* GetItemValueTip() const override;
    virtual int GetItemWidth() const override;
        // 通过 IPluginItem 继承
        const wchar_t* GetItemName() const override;
        const wchar_t* GetItemId() const override;
        const wchar_t* GetItemLableText() const override;
        const wchar_t* GetItemValueText() const override;
        const wchar_t* GetItemValueSampleText() const override;
        virtual int IsDrawResourceUsageGraph() const override;
        virtual float GetResourceUsageGraphValue() const override;

        void UpdateValue();
        const std::wstring& GetIdentifier() const;

    private:
        std::wstring identifier;
        std::wstring item_name;
        std::wstring item_value_taskbar;
        std::wstring item_value_main_wnd;
        std::wstring label_text;
        int sensor_type{};
        float item_value_num{};
    std::wstring m_identifyer;
    std::wstring m_item_name;
    std::wstring m_lable_text;
    float m_value{};
    };
}
