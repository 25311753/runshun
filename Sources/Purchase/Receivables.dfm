object ReceivablesForm: TReceivablesForm
  Left = 203
  Top = 122
  Width = 1076
  Height = 644
  Caption = #24212#25910#27454
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 996
    Top = 0
    Width = 64
    Height = 23
    Caption = #26368#23567#21270
    TabOrder = 0
  end
  object btnAdd: TButton
    Left = 76
    Top = 0
    Width = 75
    Height = 25
    Caption = #28155#21152
    TabOrder = 1
  end
  object btnMod: TButton
    Left = 150
    Top = 0
    Width = 75
    Height = 25
    Caption = #20462#25913
    TabOrder = 2
  end
  object btnNew: TButton
    Left = 1
    Top = 0
    Width = 75
    Height = 25
    Caption = #26032#22686
    TabOrder = 3
  end
  object btnOK: TButton
    Left = 541
    Top = 0
    Width = 114
    Height = 25
    Caption = #30830#35748#25910#27454
    TabOrder = 4
  end
  object pl: TPanel
    Left = 0
    Top = 26
    Width = 1060
    Height = 85
    Color = cl3DDkShadow
    TabOrder = 5
    object pl_input: TPanel
      Left = 2
      Top = 3
      Width = 1057
      Height = 50
      Color = clInactiveCaption
      TabOrder = 0
      object Panel2: TPanel
        Left = 1
        Top = 3
        Width = 60
        Height = 21
        BevelInner = bvLowered
        BevelOuter = bvLowered
        Caption = #23458#25143
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentColor = True
        ParentFont = False
        TabOrder = 0
      end
      object cbbClient: TComboBox
        Left = 61
        Top = 3
        Width = 152
        Height = 21
        AutoDropDown = True
        Color = clHighlightText
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        ItemHeight = 13
        TabOrder = 1
      end
      object Panel20: TPanel
        Left = 214
        Top = 3
        Width = 73
        Height = 21
        Alignment = taLeftJustify
        BevelInner = bvLowered
        BevelOuter = bvLowered
        Caption = #24212#25910#27454#26085#26399
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentColor = True
        ParentFont = False
        TabOrder = 2
      end
      object dtpShouldRecvDate: TDateTimePicker
        Left = 287
        Top = 3
        Width = 69
        Height = 21
        CalAlignment = dtaLeft
        Date = 40894.3857962963
        Format = 'yyyy-MM'
        Time = 40894.3857962963
        DateFormat = dfShort
        DateMode = dmUpDown
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        Kind = dtkDate
        ParseInput = False
        TabOrder = 3
      end
      object Panel9: TPanel
        Left = 357
        Top = 3
        Width = 60
        Height = 21
        BevelInner = bvLowered
        BevelOuter = bvLowered
        Caption = #24212#25910#27454
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentColor = True
        ParentFont = False
        TabOrder = 4
      end
      object edtCharge: TEdit
        Left = 417
        Top = 3
        Width = 122
        Height = 21
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 5
      end
      object Panel5: TPanel
        Left = 539
        Top = 3
        Width = 35
        Height = 21
        BevelInner = bvLowered
        BevelOuter = bvLowered
        Caption = #29366#24577
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentColor = True
        ParentFont = False
        TabOrder = 6
      end
      object cbbStatus: TComboBox
        Left = 573
        Top = 3
        Width = 79
        Height = 21
        Style = csDropDownList
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        ItemHeight = 13
        TabOrder = 7
        Items.Strings = (
          #24050#25910#27454
          #26410#25910#27454)
      end
      object Panel13: TPanel
        Left = 652
        Top = 3
        Width = 60
        Height = 21
        BevelInner = bvLowered
        BevelOuter = bvLowered
        Caption = #25910#27454#26085#26399
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentColor = True
        ParentFont = False
        TabOrder = 8
      end
      object dtpRecvDate: TDateTimePicker
        Left = 712
        Top = 3
        Width = 83
        Height = 21
        CalAlignment = dtaLeft
        Date = 40894.3686127199
        Time = 40894.3686127199
        DateFormat = dfShort
        DateMode = dmComboBox
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        Kind = dtkDate
        ParseInput = False
        TabOrder = 9
      end
      object Panel14: TPanel
        Left = 1
        Top = 26
        Width = 60
        Height = 21
        BevelInner = bvLowered
        BevelOuter = bvLowered
        Caption = #22791#27880
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentColor = True
        ParentFont = False
        TabOrder = 10
      end
      object edtBeiZhu: TEdit
        Left = 61
        Top = 26
        Width = 670
        Height = 21
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 11
      end
    end
    object pl_query: TPanel
      Left = 2
      Top = 57
      Width = 1057
      Height = 26
      Color = clInactiveCaption
      TabOrder = 1
      object Panel1: TPanel
        Left = 1
        Top = 3
        Width = 60
        Height = 21
        BevelInner = bvLowered
        BevelOuter = bvLowered
        Caption = #23458#25143
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentColor = True
        ParentFont = False
        TabOrder = 0
      end
      object cbbQryClient: TComboBox
        Left = 61
        Top = 3
        Width = 152
        Height = 21
        AutoDropDown = True
        Color = clHighlightText
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        ItemHeight = 13
        TabOrder = 1
      end
      object dtpQryRecvDateEnd: TDateTimePicker
        Left = 356
        Top = 3
        Width = 83
        Height = 21
        CalAlignment = dtaLeft
        Date = 40894.3686127199
        Time = 40894.3686127199
        DateFormat = dfShort
        DateMode = dmComboBox
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        Kind = dtkDate
        ParseInput = False
        TabOrder = 2
      end
      object Panel4: TPanel
        Left = 213
        Top = 3
        Width = 60
        Height = 21
        BevelInner = bvLowered
        BevelOuter = bvLowered
        Caption = #25910#27454#26085#26399
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentColor = True
        ParentFont = False
        TabOrder = 3
      end
      object dtpQryRecvDate: TDateTimePicker
        Left = 273
        Top = 3
        Width = 83
        Height = 21
        CalAlignment = dtaLeft
        Date = 40894.3686127199
        Time = 40894.3686127199
        DateFormat = dfShort
        DateMode = dmComboBox
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        Kind = dtkDate
        ParseInput = False
        TabOrder = 4
      end
      object Panel3: TPanel
        Left = 439
        Top = 3
        Width = 35
        Height = 21
        BevelInner = bvLowered
        BevelOuter = bvLowered
        Caption = #29366#24577
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentColor = True
        ParentFont = False
        TabOrder = 5
      end
      object cbbQryStatus: TComboBox
        Left = 473
        Top = 3
        Width = 79
        Height = 21
        Style = csDropDownList
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        ItemHeight = 13
        TabOrder = 6
        Items.Strings = (
          #24050#25910#27454
          #26410#25910#27454)
      end
      object btnQry: TButton
        Left = 713
        Top = 3
        Width = 82
        Height = 19
        Caption = #26597#35810
        TabOrder = 7
      end
    end
  end
  object lstViewDown: TListView
    Left = 1
    Top = 112
    Width = 1058
    Height = 490
    Columns = <
      item
        Caption = 'N'
        Width = 20
      end
      item
        Caption = #23458#25143
        Width = 100
      end>
    FlatScrollBars = True
    GridLines = True
    ReadOnly = True
    RowSelect = True
    SortType = stData
    TabOrder = 6
    ViewStyle = vsReport
  end
  object TrayIcon1: TTrayIcon
    Hint = #28070#39034#25253#20851
    Hide = True
    RestoreOn = imDoubleClick
    PopupMenuOn = imNone
    Icons = ImageList1
    Left = 928
  end
  object ImageList1: TImageList
    Left = 960
    Bitmap = {
      494C010101000400040010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000001000000001002000000000000010
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FFA4ADADFF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF1F4140FF006866FF008C8AFFDFE0E0FF000000FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FFF9F9F9FF003232FF003534FF006967FF008F8DFF008C8AFF729494FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF000000FF000000FFB1AE
      AEFF808484FF003534FF003635FF006B6AFF00908EFF008E8CFF008A88FF939B
      94FFFEFEFEFF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF000000FF35201EFF5110
      09FF0D2024FF003635FF004B4AFF00CFCDFF00C5C3FF00908EFF008D8BFF1285
      27FF0C831AFFC2C7C3FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF250704FF280804FF5812
      0AFF0A2224FF007877FF04ABABFF2F5370FF20B7C9FF00E7E4FF00A2A0FF177B
      33FF0C861BFF0C831AFFF9F9F9FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF270804FF290804FF6113
      0BFF065E5EFF1F5B6BFF031617FF006765FF007574FF29526AFF0BE3E6FF1D73
      40FF0D8B1CFF0C841AFFB9C1BAFF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF2A0805FF64140BFF6A2E
      2FFF0D1015FF002E2EFF003635FF006A69FF009190FF008F8DFF045C59FF2F59
      6FFF16E42EFF10A621FF7B997EFF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF7C1B11FF1F2A37FF490F
      08FF022928FF003635FF003736FF006B69FF009291FF00918FFF008F8DFF255A
      53FF135029FF2FA465FF8EAF92FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF2D2624FF280804FF6916
      0DFF002F2EFF003636FF003837FF006B6AFF009492FF009290FF00908EFF2757
      5EFF0E931DFF0C7E19FFBDC0BDFF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000ADAAAAFF280804FF2A0805FF641C
      17FF003333FF003837FF003E3EFF00A5A3FF00AFADFF009492FF009190FF2558
      67FF0E961EFF0D871BFF0C841AFF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000766C6CFF290804FF2E0905FF5D21
      21FF004342FF00A09EFF00C4C2FF00BCBAFF00C2C0FF00EEEBFF00C1BEFF1E5E
      6BFF0E991FFF0D881BFF0C861BFF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000045322FFF2A0805FF490F08FFC131
      21FF4F7182FF06ABAAFF00B6B4FF00B6B4FF00B6B4FF00B6B4FF158F95FF1FA1
      46FF20D836FF0D8D1CFF0D871BFF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000470E08FF8E1C10FF8A1B0FFF8B1C
      0FFFA22012FFBC2615FFA93731FF247492FF276E65FF12BA25FF12BF26FF11B0
      23FF10AB22FF12BB25FF14D82BFFF1F1F1FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FFD4D1D1FF86524BFF831A
      0FFF7C332AFF292E83FF0001ACFF0000B6FF0000D6FF111DD0FF246A62FF0FA1
      20FF1F9A2DFF9DB2A0FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FFA3A3B5FF17178CFF000094FF000094FF606096FFF7F7F7FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000100000000100010000000000800000000000000000000000
      000000000000000000000000FFFFFF00FEFF000000000000FC3F000000000000
      F01F000000000000E007000000000000C0030000000000008001000000000000
      8001000000000000800100000000000080010000000000008001000000000000
      0001000000000000000100000000000000010000000000000000000000000000
      8003000000000000F81F00000000000000000000000000000000000000000000
      000000000000}
  end
end