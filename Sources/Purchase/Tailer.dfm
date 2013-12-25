object TailerForm: TTailerForm
  Left = 239
  Top = 117
  Width = 1257
  Height = 782
  Caption = #25302#36710#31995#32479
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object PanelUp: TPanel
    Left = -1
    Top = 24
    Width = 1142
    Height = 225
    Color = clInactiveCaption
    TabOrder = 0
    object cbbClient: TComboBox
      Left = 275
      Top = 3
      Width = 152
      Height = 21
      AutoDropDown = True
      Color = clHighlightText
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 0
    end
    object edtLading: TEdit
      Left = 488
      Top = 3
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 1
      Text = 'edtLading'
    end
    object edtCliWorkid: TEdit
      Left = 610
      Top = 46
      Width = 122
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 9
      Text = 'edtCliWorkid'
    end
    object edtBeiZhu: TEdit
      Left = 62
      Top = 90
      Width = 670
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 13
      Text = 'edtBeiZhu'
    end
    object cbbGoodsPerf: TComboBox
      Left = 62
      Top = 46
      Width = 122
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 10
      Items.Strings = (
        #23567#21830#21697
        #20080#21333
        #27491#24120#21333)
    end
    object dtpEndDateHHMM: TDateTimePicker
      Left = 146
      Top = 3
      Width = 68
      Height = 21
      CalAlignment = dtaLeft
      Date = 40895.4886652778
      Time = 40895.4886652778
      DateFormat = dfShort
      DateMode = dmComboBox
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      Kind = dtkTime
      ParseInput = False
      TabOrder = 12
    end
    object edtContainerNo: TEdit
      Left = 796
      Top = 1
      Width = 88
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 2
      Text = 'edtContainerNo'
    end
    object cbbContainerType: TComboBox
      Left = 914
      Top = 1
      Width = 56
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      ItemIndex = 0
      TabOrder = 3
      Text = '45HQ'
      Items.Strings = (
        '45HQ'
        '45HQ')
    end
    object btnAddContainer: TButton
      Left = 1076
      Top = 23
      Width = 64
      Height = 21
      Caption = #28155#21152
      TabOrder = 5
    end
    object lstViewContainer: TListView
      Left = 736
      Top = 22
      Width = 339
      Height = 93
      Columns = <
        item
          Caption = #38598#35013#31665#21495
          Width = 147
        end
        item
          Caption = #26588#22411
          Width = 60
        end
        item
          Caption = #23553#26465#21495
          Width = 73
        end>
      GridLines = True
      ReadOnly = True
      RowSelect = True
      TabOrder = 14
      ViewStyle = vsReport
    end
    object btnModContainer: TButton
      Left = 1076
      Top = 43
      Width = 64
      Height = 22
      Caption = #20462#25913
      TabOrder = 6
    end
    object btnDelContainer: TButton
      Left = 1076
      Top = 64
      Width = 64
      Height = 23
      Caption = #21024#38500
      TabOrder = 7
    end
    object edtSealId: TEdit
      Left = 1015
      Top = 1
      Width = 124
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 4
      Text = 'edtSealId'
    end
    object dtpEndDateYYYYMMDD: TDateTimePicker
      Left = 62
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
      TabOrder = 11
    end
    object Panel2: TPanel
      Left = 215
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
      TabOrder = 15
    end
    object Panel3: TPanel
      Left = 428
      Top = 3
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #25552#21333#21495
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 16
    end
    object Panel4: TPanel
      Left = 736
      Top = 1
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #38598#35013#31665#21495
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 17
    end
    object Panel5: TPanel
      Left = 885
      Top = 1
      Width = 30
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #26588#22411
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 18
    end
    object Panel6: TPanel
      Left = 971
      Top = 1
      Width = 45
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #23553#26465#21495
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 19
    end
    object Panel7: TPanel
      Left = 185
      Top = 46
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #32852#31995#20154
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 20
    end
    object Panel10: TPanel
      Left = 550
      Top = 46
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #36816#36755#20844#21496
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 21
    end
    object Panel11: TPanel
      Left = 2
      Top = 46
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #36135#29289#24615#36136
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 22
    end
    object Panel13: TPanel
      Left = 2
      Top = 3
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #20570#26588#26085#26399
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 23
    end
    object Panel14: TPanel
      Left = 2
      Top = 90
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
      TabOrder = 24
    end
    object edtBoatNo: TEdit
      Left = 245
      Top = 46
      Width = 122
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 8
      Text = 'edtBoatNo'
    end
    object Panel1: TPanel
      Left = 2
      Top = 24
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #35013#36135#22320#22336
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 25
    end
    object Edit1: TEdit
      Left = 62
      Top = 24
      Width = 670
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 26
      Text = 'edtBeiZhu'
    end
    object Panel8: TPanel
      Left = 368
      Top = 46
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #32852#31995#30005#35805
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 27
    end
    object Edit2: TEdit
      Left = 428
      Top = 46
      Width = 122
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 28
      Text = 'edtBoatNo'
    end
    object Panel9: TPanel
      Left = 2
      Top = 68
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #36816#36153
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 29
    end
    object Edit3: TEdit
      Left = 62
      Top = 68
      Width = 122
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 30
      Text = 'edtBoatNo'
    end
    object Panel12: TPanel
      Left = 185
      Top = 68
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #22806#27966#36816#36153
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 31
    end
    object Edit4: TEdit
      Left = 245
      Top = 68
      Width = 122
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 32
      Text = 'edtBoatNo'
    end
    object Panel24: TPanel
      Left = 368
      Top = 68
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #36710#29260
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 33
    end
    object Edit5: TEdit
      Left = 428
      Top = 68
      Width = 122
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 34
      Text = 'edtBoatNo'
    end
    object Panel25: TPanel
      Left = 550
      Top = 68
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #21496#26426
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 35
    end
    object Edit6: TEdit
      Left = 610
      Top = 68
      Width = 122
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 36
      Text = 'edtBoatNo'
    end
    object Panel26: TPanel
      Left = 1
      Top = 117
      Width = 1140
      Height = 50
      Color = clInactiveCaption
      TabOrder = 37
      object cbb1: TComboBox
        Left = 0
        Top = 2
        Width = 114
        Height = 21
        Style = csDropDownList
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        ItemHeight = 13
        TabOrder = 0
      end
      object edtCharge1: TEdit
        Left = 113
        Top = 2
        Width = 80
        Height = 21
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 1
      end
      object Panel21: TPanel
        Left = 53
        Top = 24
        Width = 60
        Height = 21
        BevelInner = bvLowered
        BevelOuter = bvLowered
        Caption = #25104#26412
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentColor = True
        ParentFont = False
        TabOrder = 2
      end
      object Edit7: TEdit
        Left = 113
        Top = 24
        Width = 80
        Height = 21
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 3
      end
      object ComboBox1: TComboBox
        Left = 199
        Top = 2
        Width = 114
        Height = 21
        Style = csDropDownList
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        ItemHeight = 13
        TabOrder = 4
      end
      object Panel27: TPanel
        Left = 253
        Top = 24
        Width = 60
        Height = 21
        BevelInner = bvLowered
        BevelOuter = bvLowered
        Caption = #25104#26412
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentColor = True
        ParentFont = False
        TabOrder = 5
      end
      object Edit8: TEdit
        Left = 313
        Top = 24
        Width = 80
        Height = 21
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 6
      end
      object Edit9: TEdit
        Left = 313
        Top = 2
        Width = 80
        Height = 21
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 7
      end
      object ComboBox4: TComboBox
        Left = 800
        Top = 2
        Width = 114
        Height = 21
        Style = csDropDownList
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        ItemHeight = 13
        TabOrder = 8
      end
      object Edit14: TEdit
        Left = 913
        Top = 2
        Width = 80
        Height = 21
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 9
      end
      object Edit15: TEdit
        Left = 913
        Top = 24
        Width = 80
        Height = 21
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 10
      end
      object Panel30: TPanel
        Left = 853
        Top = 24
        Width = 60
        Height = 21
        BevelInner = bvLowered
        BevelOuter = bvLowered
        Caption = #25104#26412
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentColor = True
        ParentFont = False
        TabOrder = 11
      end
      object ComboBox2: TComboBox
        Left = 400
        Top = 2
        Width = 114
        Height = 21
        Style = csDropDownList
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        ItemHeight = 13
        TabOrder = 12
      end
      object Panel28: TPanel
        Left = 453
        Top = 24
        Width = 60
        Height = 21
        BevelInner = bvLowered
        BevelOuter = bvLowered
        Caption = #25104#26412
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentColor = True
        ParentFont = False
        TabOrder = 13
      end
      object Edit10: TEdit
        Left = 513
        Top = 24
        Width = 80
        Height = 21
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 14
      end
      object Edit11: TEdit
        Left = 513
        Top = 2
        Width = 80
        Height = 21
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 15
      end
      object ComboBox3: TComboBox
        Left = 600
        Top = 2
        Width = 114
        Height = 21
        Style = csDropDownList
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        ItemHeight = 13
        TabOrder = 16
      end
      object Panel29: TPanel
        Left = 653
        Top = 24
        Width = 60
        Height = 21
        BevelInner = bvLowered
        BevelOuter = bvLowered
        Caption = #25104#26412
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentColor = True
        ParentFont = False
        TabOrder = 17
      end
      object Edit12: TEdit
        Left = 713
        Top = 24
        Width = 80
        Height = 21
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 18
      end
      object Edit13: TEdit
        Left = 713
        Top = 2
        Width = 80
        Height = 21
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 19
      end
      object Panel31: TPanel
        Left = 997
        Top = 3
        Width = 60
        Height = 21
        BevelInner = bvLowered
        BevelOuter = bvLowered
        Caption = #21512#35745
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentColor = True
        ParentFont = False
        TabOrder = 20
      end
      object Edit16: TEdit
        Left = 1057
        Top = 3
        Width = 80
        Height = 21
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 21
      end
      object Panel32: TPanel
        Left = 997
        Top = 24
        Width = 60
        Height = 21
        BevelInner = bvLowered
        BevelOuter = bvLowered
        Caption = #21512#35745
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentColor = True
        ParentFont = False
        TabOrder = 22
      end
      object Edit17: TEdit
        Left = 1057
        Top = 24
        Width = 80
        Height = 21
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 23
      end
    end
    object Panel45: TPanel
      Left = 0
      Top = 167
      Width = 1140
      Height = 5
      Color = 16349446
      TabOrder = 38
    end
  end
  object btnAdd: TButton
    Left = 1
    Top = 0
    Width = 75
    Height = 25
    Caption = #28155#21152
    TabOrder = 1
  end
  object btnMod: TButton
    Left = 75
    Top = 0
    Width = 75
    Height = 25
    Caption = #20462#25913
    TabOrder = 2
  end
  object btnDel: TButton
    Left = 149
    Top = 0
    Width = 75
    Height = 25
    Caption = #21024#38500
    TabOrder = 3
  end
  object PanelUpQuery: TPanel
    Left = -1
    Top = 196
    Width = 1140
    Height = 51
    Color = clInactiveCaption
    TabOrder = 4
    object edtQryLading: TEdit
      Left = 254
      Top = 3
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 1
      Text = 'edtQryLading'
    end
    object edtQryJZS: TEdit
      Left = 436
      Top = 3
      Width = 142
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 5
      Text = 'edtQryJZS'
    end
    object btnQuery: TButton
      Left = 1005
      Top = 27
      Width = 66
      Height = 20
      Caption = #26597#35810
      TabOrder = 4
    end
    object dtpQryAcceptDate: TDateTimePicker
      Left = 61
      Top = 25
      Width = 83
      Height = 21
      CalAlignment = dtaLeft
      Date = 40894.3857962963
      Time = 40894.3857962963
      DateFormat = dfShort
      DateMode = dmComboBox
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      Kind = dtkDate
      ParseInput = False
      TabOrder = 2
    end
    object dtpQryAcceptDateEnd: TDateTimePicker
      Left = 145
      Top = 25
      Width = 83
      Height = 21
      CalAlignment = dtaLeft
      Date = 40894.3921510648
      Time = 40894.3921510648
      DateFormat = dfShort
      DateMode = dmComboBox
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      Kind = dtkDate
      ParseInput = False
      TabOrder = 3
    end
    object cbbQryClient: TComboBox
      Left = 61
      Top = 3
      Width = 132
      Height = 21
      AutoDropDown = True
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 0
    end
    object Panel16: TPanel
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
      TabOrder = 6
    end
    object Panel17: TPanel
      Left = 194
      Top = 3
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #25552#21333#21495
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 7
    end
    object Panel18: TPanel
      Left = 376
      Top = 3
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #38598#35013#31665#21495
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 8
    end
    object Panel20: TPanel
      Left = 1
      Top = 25
      Width = 60
      Height = 21
      Alignment = taLeftJustify
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #25509#21333#26085#26399
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 9
    end
    object Panel23: TPanel
      Left = 945
      Top = 3
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #36135#29289#24615#36136
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 10
    end
    object cbbGoodsPerfQry: TComboBox
      Left = 1005
      Top = 3
      Width = 133
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 11
      Items.Strings = (
        ''
        #23567#21830#21697
        #20080#21333
        #27491#24120#21333)
    end
    object btnClearQryCond: TButton
      Left = 1072
      Top = 27
      Width = 65
      Height = 20
      Caption = #28165#31354
      TabOrder = 12
    end
    object Panel15: TPanel
      Left = 579
      Top = 3
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #36816#36755#20844#21496
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 13
    end
    object Edit18: TEdit
      Left = 639
      Top = 3
      Width = 122
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 14
      Text = 'edtCliWorkid'
    end
    object Panel19: TPanel
      Left = 762
      Top = 3
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #21496#26426
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 15
    end
    object Edit19: TEdit
      Left = 822
      Top = 3
      Width = 122
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 16
      Text = 'edtBoatNo'
    end
  end
  object btnCancel: TButton
    Left = 360
    Top = 0
    Width = 63
    Height = 25
    Caption = #21462#28040
    TabOrder = 5
  end
  object btnOK: TButton
    Left = 297
    Top = 0
    Width = 63
    Height = 25
    Caption = #30830#23450
    TabOrder = 6
  end
  object Button1: TButton
    Left = 1177
    Top = 0
    Width = 64
    Height = 23
    Caption = #26368#23567#21270
    TabOrder = 7
  end
  object lstViewDown: TListView
    Left = 0
    Top = 256
    Width = 1276
    Height = 444
    Columns = <
      item
        Caption = 'N'
        Width = 20
      end
      item
        Caption = #20570#26588#26085#26399
        Width = 75
      end
      item
        Caption = #23458#25143
        Width = 60
      end
      item
        Caption = #25552#21333#21495
        Width = 120
      end
      item
        Caption = #38598#35013#31665#21495
        Width = 90
      end
      item
        Caption = #23553#26465#21495
        Width = 80
      end
      item
        Caption = #26588#22411
        Width = 40
      end
      item
        Caption = #26588#25968
        Width = 60
      end
      item
        Caption = #36816#36755#20844#21496
        Width = 65
      end
      item
        Caption = #21496#26426
      end
      item
        Caption = #36710#29260
        Width = 70
      end
      item
        Caption = #36135#29289#24615#36136
        Width = 70
      end
      item
        Caption = #36816#36153
        Width = 120
      end
      item
        Caption = #22806#27966#36816#36153
        Width = 70
      end
      item
        Caption = #20195#22443#36153#21512#35745
        Width = 120
      end
      item
        Caption = #25104#26412#21512#35745
        Width = 100
      end
      item
        Caption = #21033#28070
      end>
    FlatScrollBars = True
    GridLines = True
    ReadOnly = True
    RowSelect = True
    SortType = stData
    TabOrder = 8
    ViewStyle = vsReport
  end
  object btnPrnOutCar: TButton
    Left = 735
    Top = 0
    Width = 106
    Height = 25
    Caption = #29983#25104#27966#36710#21333
    TabOrder = 9
  end
  object TrayIcon1: TTrayIcon
    Hint = #28070#39034#25253#20851
    Hide = True
    RestoreOn = imDoubleClick
    PopupMenuOn = imNone
    Icons = ImageList1
    Left = 1128
  end
  object ImageList1: TImageList
    Left = 1160
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
