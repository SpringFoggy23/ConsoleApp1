VERSION 5.00
Begin VB.Form Form1 
   AutoRedraw      =   -1  'True
   Caption         =   "点球游戏"
   ClientHeight    =   5400
   ClientLeft      =   1935
   ClientTop       =   2265
   ClientWidth     =   10215
   LinkTopic       =   "Form1"
   ScaleHeight     =   5400
   ScaleWidth      =   10215
   Begin VB.CommandButton Command3 
      Caption = "退出游戏"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   14.25
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   360
      TabIndex        =   15
      Top             =   600
      Width           =   1455
   End
   Begin VB.Timer Timer4 
      Enabled         =   0   'False
      Interval        =   1
      Left            =   600
      Top             =   3240
   End
   Begin VB.Timer Timer3 
      Enabled         =   0   'False
      Interval        =   15
      Left            =   600
      Top             =   3840
   End
   Begin VB.CommandButton Command5 
      Caption         =   "必杀技：神奥义 断子绝孙"
      Height          =   615
      Left            =   8400
      TabIndex        =   7
      Top             =   3120
      Visible         =   0   'False
      Width           =   1455
   End
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   15
      Left            =   600
      Top             =   4440
   End
   Begin VB.CommandButton Command2 
      Caption         =   "往右踢"
      Height          =   495
      Left            =   6120
      TabIndex        =   1
      Top             =   4560
      Width           =   1215
   End
   Begin VB.CommandButton Command1 
      Caption         =   "往左踢"
      Height          =   495
      Left            =   3240
      TabIndex        =   0
      Top             =   4560
      Width           =   1215
   End
   Begin VB.Label Label12 
      BackColor       =   &H80000000&
      BackStyle       =   0  'Transparent
      Caption         =   "红领巾20"
      BeginProperty Font 
         Name            =   "微软雅黑"
         Size            =   15
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000000FF&
      Height          =   375
      Left            =   3360
      TabIndex        =   14
      Top             =   2880
      Visible         =   0   'False
      Width           =   1335
   End
   Begin VB.Label Label11 
      BackColor       =   &H80000016&
      Caption         =   "Ready"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   15
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000000FF&
      Height          =   375
      Left            =   9480
      TabIndex        =   13
      Top             =   2040
      Visible         =   0   'False
      Width           =   855
   End
   Begin VB.Label Label10 
      Caption         =   "Ready"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   15
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000000FF&
      Height          =   375
      Left            =   9360
      TabIndex        =   12
      Top             =   240
      Visible         =   0   'False
      Width           =   855
   End
   Begin VB.Label Label9 
      Caption         =   "0"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   15
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   7800
      TabIndex        =   11
      Top             =   240
      Width           =   855
   End
   Begin VB.Label Label8 
      Caption         =   " %"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   15
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   8640
      TabIndex        =   10
      Top             =   240
      Width           =   495
   End
   Begin VB.Label Label7 
      Caption         =   " %"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   15
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   8640
      TabIndex        =   9
      Top             =   2040
      Width           =   495
   End
   Begin VB.Label Label6 
      Caption         =   "0"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   15
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   7800
      TabIndex        =   8
      Top             =   2040
      Width           =   855
   End
   Begin VB.Label Label5 
      BackStyle       =   0  'Transparent
      Caption         =   "点球大战"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   42
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H0000FFFF&
      Height          =   1215
      Left            =   3360
      TabIndex        =   6
      Top             =   840
      Width           =   3735
   End
   Begin VB.Label Label4 
      Caption         =   "0"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   21.75
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000000FF&
      Height          =   615
      Left            =   9240
      TabIndex        =   5
      Top             =   1440
      Width           =   1455
   End
   Begin VB.Label Label3 
      Caption         =   "0"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   21.75
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000000FF&
      Height          =   615
      Left            =   9240
      TabIndex        =   4
      Top             =   600
      Width           =   1455
   End
   Begin VB.Label Label2 
      Caption         =   "电脑："
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   21.75
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000000FF&
      Height          =   615
      Left            =   7800
      TabIndex        =   3
      Top             =   1440
      Width           =   1455
   End
   Begin VB.Label Label1 
      Caption         =   "玩家："
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   21.75
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000000FF&
      Height          =   615
      Left            =   7800
      TabIndex        =   2
      Top             =   600
      Width           =   1455
   End
   Begin VB.Image Image3 
      Height          =   615
      Left            =   4920
      Picture         =   "Form1.frx":0000
      Stretch         =   -1  'True
      Top             =   4440
      Width           =   615
   End
   Begin VB.Image Image2 
      Height          =   1425
      Left            =   4440
      Picture         =   "Form1.frx":7677
      Stretch         =   -1  'True
      Top             =   2400
      Width           =   1755
   End
   Begin VB.Image Image1 
      Height          =   5415
      Left            =   0
      Picture         =   "Form1.frx":96EF
      Stretch         =   -1  'True
      Top             =   0
      Width           =   10215
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Declare Function timeGetTime Lib "winmm.dll" () As Long
Dim x, y, z As Integer
Private Sub Command1_Click()
Timer1.Enabled = True
x = -100
Randomize
y = Int(Rnd() * 2)
If y = 0 Then
    z = -80
    Label4.Caption = Label4.Caption + 1
    Label6.Caption = Label6.Caption + 10
Else
    z = 80
    Label3.Caption = Label3.Caption + 1
    Label9.Caption = Label9.Caption + 10
End If
If Label9.Caption = 100 Then
    Label10.Visible = True
    Command5.Visible = True
    Command1.Visible = False
    Command2.Visible = False
End If
If Label6.Caption = 100 Then
   Dim Savetime As Double
   Label12.Visible = True
   Savetime = timeGetTime '记下开始时的时间
   While timeGetTime < Savetime + 1000 '循环等待
   DoEvents '转让控制权，以便让操作系统处理其它的事件。
   Wend
   Label12.Visible = False
   Label6.Caption = 0
   Label9.Caption = Label9.Caption - 20
   Label3.Caption = Label3.Caption - 2
End If
End Sub

Private Sub Command2_Click()
Timer1.Enabled = True
x = 100
Randomize
y = Int(Rnd() * 2)

If y = 0 Then
    z = -80
    Label3.Caption = Label3.Caption + 1
    Label9.Caption = Label9.Caption + 10
Else
    z = 80
    Label4.Caption = Label4.Caption + 1
    Label6.Caption = Label6.Caption + 10
End If
If Label9.Caption = 100 Then
    Label10.Visible = True
    Command5.Visible = True
    Command1.Visible = False
    Command2.Visible = False
End If
If Label6.Caption = 100 Then
   Dim Savetime As Double
   Label12.Visible = True
   Savetime = timeGetTime '记下开始时的时间
   While timeGetTime < Savetime + 1000 '循环等待
   DoEvents '转让控制权，以便让操作系统处理其它的事件。
   Wend
   Label12.Visible = False
   Label6.Caption = 0
   Label9.Caption = Label9.Caption - 20
   Label3.Caption = Label3.Caption - 2
End If
End Sub

Private Sub Command3_Click()
End
End Sub

Private Sub Command5_Click()
Timer3.Enabled = True
x = -100
 Label4.Caption = Label4.Caption - 5
 Command5.Visible = False
 Label10.Visible = False
 Label9.Caption = 0
 Label6.Caption = 0
 Command1.Visible = True
 Command2.Visible = True
End Sub


Private Sub Timer1_Timer()
If Image3.Left > 3100 And Image3.Left < 6720 Then
    Image3.Left = Image3.Left + x
    Image3.Top = Image3.Top - 100
    Image2.Left = Image2.Left + z
Else
    Image3.Left = 5040
    Image3.Top = 4440
    Timer1.Enabled = False

     Image2.Left = 4560
End If
End Sub

Private Sub Timer3_Timer()
If Image3.Top > 3000 And Image3.Top < 4560 Then
    Image3.Top = Image3.Top + x
Else
   
    Timer3.Enabled = False
    Timer4.Enabled = True
End If
End Sub

Private Sub Timer4_Timer()
If Image2.Top > -960 And Image2.Top < 4560 Then
    Image2.Top = Image2.Top + x + 10
Else
    Image2.Top = 2400
    Image2.Left = 4440
    Image3.Top = 4440
    Timer4.Enabled = False
End If
End Sub

