object AskPurchaseSetSHForm: TAskPurchaseSetSHForm
  Left = 210
  Top = 110
  Width = 696
  Height = 480
  Caption = #35531#36092#21934#25351#27966#37319#36092#32147#36774
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = #26032#32048#26126#39636
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poScreenCenter
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object txtTitle: TLabel
    Left = 184
    Top = 8
    Width = 297
    Height = 33
    Caption = #35531#36092#21934#25351#27966#37319#36092#32147#36774
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = #27161#26999#39636
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 536
    Top = 48
    Width = 78
    Height = 13
    Caption = #35531#36092#21934#32232#34399#65306
  end
  object txtStockHandle: TLabel
    Left = 536
    Top = 104
    Width = 65
    Height = 13
    Caption = #37319#36092#32147#36774#65306
  end
  object lstView: TListView
    Left = 8
    Top = 48
    Width = 505
    Height = 393
    Columns = <
      item
        Caption = #35531#36092#21934#34399
        Width = 70
      end
      item
        Caption = #36664#20837#26085#26399
        Width = 70
      end
      item
        Caption = #25509#26696#26085#26399
        Width = 70
      end
      item
        Caption = #21015#21360#26085#26399
        Width = 70
      end
      item
        Caption = #25509#26696#24460#20462#25913#26085#26399
        Width = 110
      end
      item
        Caption = #37319#36092#32147#36774
        Width = 80
      end>
    GridLines = True
    HideSelection = False
    ReadOnly = True
    RowSelect = True
    TabOrder = 0
    ViewStyle = vsReport
    OnClick = lstViewClick
    OnSelectItem = lstViewSelectItem
  end
  object edtID: TEdit
    Left = 536
    Top = 64
    Width = 105
    Height = 21
    CharCase = ecUpperCase
    MaxLength = 8
    TabOrder = 1
    Text = 'EDTID'
    OnKeyDown = edtIDKeyDown
  end
  object btnRefresh: TButton
    Left = 536
    Top = 168
    Width = 105
    Height = 25
    Caption = #21047'    '#26032
    TabOrder = 2
    OnClick = btnRefreshClick
  end
  object btnAfm: TButton
    Left = 536
    Top = 264
    Width = 105
    Height = 25
    Caption = #25351'    '#27966
    TabOrder = 3
    OnClick = btnAfmClick
  end
  object btnDeafm: TButton
    Left = 536
    Top = 312
    Width = 105
    Height = 25
    Caption = #35299#38500#25351#27966
    TabOrder = 4
    OnClick = btnDeafmClick
  end
  object btnExit: TButton
    Left = 536
    Top = 360
    Width = 105
    Height = 25
    Caption = #36864'    '#20986
    TabOrder = 5
    OnClick = btnExitClick
  end
  object btnDetail: TButton
    Left = 536
    Top = 216
    Width = 105
    Height = 25
    Caption = #35443#32048#36039#26009
    TabOrder = 6
    OnClick = btnDetailClick
  end
  object lstStockHandle: TComboBox
    Left = 536
    Top = 120
    Width = 105
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 7
  end
end
