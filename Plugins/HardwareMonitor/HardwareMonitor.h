#pragma once
#include "../../include/ITMPlugin.h"
#include "HardwareMonitorItem.h"
#include <vector>
#include <map>
#include <string>

// LibreHardwareMonitorLib.dll
#using "LibreHardwareMonitorLib.dll"
using namespace LibreHardwareMonitor::Hardware;

namespace HardwareMonitor
{
    struct ItemInfo
    {
        std::wstring identifyer;
        int decimal_places{ 1 };
        bool specify_value_width{ true };
        int value_width{ 3 };
        std::wstring unit;
        bool show_unit{ true };
    };

    class CSettings
    {
    public:
        std::vector<ItemInfo> items_info;
        bool hardware_info_auto_refresh{};
        bool show_mouse_tooltip{ true };

        const ItemInfo& GetItemInfo(const std::wstring& identifyer) const
        {
            for (const auto& item : items_info)
            {
                if (item.identifyer == identifyer)
                    return item;
            }
            static ItemInfo default_item_info;
            return default_item_info;
        }
    };

    class CHardwareMonitor :
        public ITMPlugin
    {
    private:
        CHardwareMonitor();
        static CHardwareMonitor* m_pIns;
        ITrafficMonitor* m_pMainApp{};
        std::vector<CHardwareMonitorItem> m_items;
        std::map<std::wstring, std::wstring> m_item_names;
        std::wstring m_config_path;
        CSettings m_settings;
        int m_dpi{};
        std::map<const wchar_t*, std::wstring> string_table;
        struct TM_SETTINGS
        {
            bool main_wnd_sperate_with_space{};
            bool taskbar_sperate_with_space{};
            bool is_taskbar{};
        } m_tm_settings;

    public:
        ~CHardwareMonitor();
        static CHardwareMonitor* GetInstance();
        const std::wstring& StringRes(const wchar_t* name);
        bool AddDisplayItem(ISensor^ sensor);
        bool IsDisplayItemExist(const std::wstring& identifyer);
        bool RemoveDisplayItem(int index);
        std::wstring GetItemName(const std::wstring& identifier);
        const std::wstring& GetConfigPath() const;
        const CSettings& GetSettings() const { return m_settings; }

        void LoadConfig(const std::wstring& config_dir);
        void SaveConfig();

        int DPI(int pixel) const;

        ITrafficMonitor* GetMainApp() const;

        static void ShowErrorMessage(System::Exception^ e);

        // 通过 ITMPlugin 继承
        virtual int GetItemCount() const override { return static_cast<int>(m_items.size()); }
        virtual IPluginItem* GetItem(int index) override;
        virtual void DataRequired() override;
        virtual const wchar_t* GetInfo(PluginInfoIndex index) override;
        virtual const wchar_t* GetTooltipInfo() override;
        virtual OptionReturn ShowOptionsDialog(void* hParent) override;
        virtual void OnExtenedInfo(ExtendedInfoIndex index, const wchar_t* data) override;
        virtual void* GetPluginIcon() override;
        virtual int GetCommandCount() override;
        virtual const wchar_t* GetCommandName(int command_index) override;
        virtual void OnPluginCommand(int command_index, void* hWnd, void* para) override;
        virtual void OnInitialize(ITrafficMonitor* pApp) override;
    };
}
