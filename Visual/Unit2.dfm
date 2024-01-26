object Form2: TForm2
  Left = 0
  Top = 0
  Caption = 'Minesweeper'
  ClientHeight = 448
  ClientWidth = 852
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OnCreate = FormCreate
  TextHeight = 13
  object LabeledEdit1: TLabeledEdit
    Left = 16
    Top = 40
    Width = 121
    Height = 21
    EditLabel.Width = 79
    EditLabel.Height = 13
    EditLabel.Caption = 'Columns number'
    TabOrder = 0
    Text = ''
  end
  object LabeledEdit2: TLabeledEdit
    Left = 168
    Top = 40
    Width = 121
    Height = 21
    EditLabel.Width = 65
    EditLabel.Height = 13
    EditLabel.Caption = 'Rows number'
    TabOrder = 1
    Text = ''
  end
  object LabeledEdit3: TLabeledEdit
    Left = 320
    Top = 40
    Width = 121
    Height = 21
    EditLabel.Width = 52
    EditLabel.Height = 13
    EditLabel.Caption = 'Mine count'
    TabOrder = 2
    Text = ''
  end
  object DrawGrid1: TDrawGrid
    Left = 8
    Top = 80
    Width = 480
    Height = 270
    DefaultColWidth = 25
    DefaultRowHeight = 25
    DefaultDrawing = False
    FixedCols = 0
    FixedRows = 0
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing, goFixedRowDefAlign]
    TabOrder = 3
    Visible = False
    OnDrawCell = DrawGrid1DrawCell
    OnMouseDown = DrawGrid1MouseDown
    OnSelectCell = DrawGrid1SelectCell
  end
  object Button1: TButton
    Left = 488
    Top = 38
    Width = 89
    Height = 25
    Caption = 'Create game'
    TabOrder = 4
    OnClick = Button1Click
  end
end
