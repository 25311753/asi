object HandleManForm: THandleManForm
  Left = 278
  Top = 118
  Width = 787
  Height = 531
  Caption = #29376#24907#27284#36664#20837
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poScreenCenter
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label4: TLabel
    Left = 330
    Top = 16
    Width = 165
    Height = 33
    Caption = #32147#36774#20154#21729#27284
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = #27161#26999#39636
    Font.Style = [fsBold]
    ParentFont = False
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 64
    Width = 761
    Height = 433
    TabOrder = 0
    object msgState: TLabel
      Left = 24
      Top = 404
      Width = 377
      Height = 13
      AutoSize = False
      Caption = #24037#20316#29376#24907#65306
    end
    object ListView1: TListView
      Left = 24
      Top = 96
      Width = 553
      Height = 297
      Columns = <
        item
          Caption = #32232#34399
        end
        item
          Caption = #21517#31281
          Width = 150
        end
        item
          Caption = #37096#38272
          Width = 150
        end
        item
          Caption = #20998#27231#34399#30908
          Width = 80
        end>
      GridLines = True
      HideSelection = False
      ReadOnly = True
      RowSelect = True
      TabOrder = 0
      ViewStyle = vsReport
      OnClick = ListView1Click
    end
  end
  object Panel1: TPanel
    Left = 24
    Top = 80
    Width = 737
    Height = 73
    TabOrder = 1
    object Label2: TLabel
      Left = 16
      Top = 12
      Width = 36
      Height = 13
      Caption = #32232#34399#65306
    end
    object Label3: TLabel
      Left = 96
      Top = 12
      Width = 36
      Height = 13
      Caption = #21517#31281#65306
    end
    object Label1: TLabel
      Left = 264
      Top = 12
      Width = 36
      Height = 13
      Caption = #37096#38272#65306
    end
    object Label5: TLabel
      Left = 424
      Top = 13
      Width = 60
      Height = 13
      Caption = #20998#27231#34399#30908#65306
    end
    object edtID: TEdit
      Left = 16
      Top = 28
      Width = 65
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 6
      TabOrder = 0
      Text = 'EDTID'
    end
    object edtName: TEdit
      Left = 96
      Top = 28
      Width = 153
      Height = 21
      MaxLength = 10
      TabOrder = 1
      Text = 'edtName'
    end
    object btnOK0: TButton
      Left = 672
      Top = 8
      Width = 57
      Height = 25
      Caption = #30906#23450
      TabOrder = 4
      OnClick = btnOK0Click
    end
    object btnCancel0: TButton
      Left = 672
      Top = 40
      Width = 57
      Height = 25
      Cancel = True
      Caption = #21462#28040
      TabOrder = 5
      OnClick = btnCancel0Click
    end
    object lstDep: TComboBox
      Left = 256
      Top = 28
      Width = 145
      Height = 21
      ItemHeight = 13
      MaxLength = 6
      TabOrder = 2
      Text = 'lstDep'
    end
    object edtTel: TEdit
      Left = 424
      Top = 29
      Width = 121
      Height = 21
      MaxLength = 4
      TabOrder = 3
      Text = 'edtTel'
    end
  end
  object btnAddNew: TButton
    Left = 624
    Top = 240
    Width = 129
    Height = 25
    Caption = #26032'    '#22686
    TabOrder = 2
    OnClick = btnAddNewClick
  end
  object btnEdit: TButton
    Left = 624
    Top = 272
    Width = 129
    Height = 25
    Caption = #20462'    '#25913
    TabOrder = 3
    OnClick = btnEditClick
  end
  object btnRefresh: TButton
    Left = 624
    Top = 336
    Width = 129
    Height = 25
    Caption = #21047'    '#26032
    TabOrder = 4
    OnClick = btnRefreshClick
  end
  object btnExit: TButton
    Left = 624
    Top = 400
    Width = 129
    Height = 25
    Caption = #36864'    '#20986
    TabOrder = 5
    OnClick = btnExitClick
  end
  object btnDelete: TButton
    Left = 624
    Top = 304
    Width = 129
    Height = 25
    Caption = #21034'    '#38500
    TabOrder = 6
    OnClick = btnDeleteClick
  end
  object btnPrint: TButton
    Left = 624
    Top = 368
    Width = 129
    Height = 25
    Caption = #21015'    '#21360
    TabOrder = 7
    OnClick = btnPrintClick
  end
end
