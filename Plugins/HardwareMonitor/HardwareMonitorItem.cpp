#include "stdafx.h"
#include "HardwareMonitorItem.h"
#include "HardwareMonitorHelper.h"
#include "Common.h"
#include "HardwareMonitor.h"

namespace HardwareMonitor
{
    // 原有构造函数实现
    CHardwareMonitorItem::CHardwareMonitorItem(const std::wstring& identifyer, const std::wstring& item_name, const std::wstring& lable_text)
        : m_identifyer(identifyer), m_item_name(item_name), m_lable_text(lable_text)
    {
    }

    // ==================== 新增构造函数的实现 ====================
    CHardwareMonitorItem::CHardwareMonitorItem(const std::wstring& identifyer, const std::wstring& item_name, const std::wstring& lable_text, bool is_graph, GraphType graph_mode)
        : m_identifyer(identifyer), m_item_name(item_name), m_lable_text(lable_text)
    {
        // 在此设置从基类继承的成员
        show_graph = is_graph;
        graph_type = graph_mode;
    }
    // ==========================================================

    CHardwareMonitorItem::~CHardwareMonitorItem()
    {
    }

    const wchar_t* CHardwareMonitorItem::GetItemName() const
    {
        return m_item_name.c_str();
    }

    const wchar_t* CHardwareMonitorItem::GetItemLableText() const
    {
        return m_lable_text.c_str();
    }

    const wchar_t* CHardwareMonitorItem::GetItemValueText() const
    {
        static std::wstring str;
        const auto& settings = CHardwareMonitor::GetInstance()->GetSettings().GetItemInfo(m_identifyer);
        if (settings.specify_value_width)
        {
            wchar_t format_str[16];
            swprintf_s(format_str, L"%%%d.%df", settings.value_width, settings.decimal_places);
            wchar_t buff[32];
            swprintf_s(buff, format_str, m_value);
            str = buff;
        }
        else
        {
            wchar_t format_str[16];
            swprintf_s(format_str, L"%%.%df", settings.decimal_places);
            wchar_t buff[32];
            swprintf_s(buff, format_str, m_value);
            str = buff;
        }
        if (settings.show_unit)
            str += settings.unit;
        return str.c_str();
    }

    const wchar_t* CHardwareMonitorItem::GetItemValueTip() const
    {
        static std::wstring str;
        wchar_t buff[32];
        swprintf_s(buff, L"%.1f", m_value);
        str = buff;
        const auto& settings = CHardwareMonitor::GetInstance()->GetSettings().GetItemInfo(m_identifyer);
        if (settings.show_unit)
            str += settings.unit;
        return str.c_str();
    }

    int CHardwareMonitorItem::GetItemWidth() const
    {
        return 0;
    }

    void CHardwareMonitorItem::UpdateValue()
    {
        ISensor^ sensor = HardwareMonitorHelper::FindSensorByIdentifyer(gcnew String(m_identifyer.c_str()));
        if (sensor != nullptr && sensor->Value->HasValue)
        {
            m_value = sensor->Value->Value;
        }
    }
}
