const electron = require('electron');
const { app, BrowserWindow, Menu, Tray, nativeImage } = require('electron');
const ipcMain = require('electron').ipcMain;
const path = require('path');

let win;
let tray = null;

const iconPath = path.join(__dirname, 'resources/icon.png');
let trayIcon = nativeImage.createFromPath(iconPath);
trayIcon.resize({ width:'16', height:'16' });

function createWindow () {
    var screenElectron = electron.screen;
    var mainScreen = screenElectron.getPrimaryDisplay();
    var dimensions = mainScreen.workAreaSize;
    const width = 452, height = 640;
    win = new BrowserWindow({ width: width, height: height, x: dimensions.width - width, y: dimensions.height - height, frame: false, skipTaskbar: true});

    win.setAlwaysOnTop(true);

    win.webContents.send('pin', true);

    win.setFullScreenable(false);

    win.setMaximizable(false);

    win.setMenu(null);

    win.setOpacity(0.96);

    win.setIcon(trayIcon);

    win.setBackgroundColor('#2b2b2b');

    win.loadFile('index.html');

    win.on('minimize', (event) => {
        event.preventDefault();
        win.hide();
    });
    
    win.on('show', function () {
        tray.setHighlightMode('always');
    })
}

ipcMain.on('exitButton', (event, arg) => {
    if (!app.isQuiting) {
        event.preventDefault();
        win.hide();
        event.returnValue = false;
      }
})

//TODO: MINIMIZE THE IF/ELSE STATEMENT TO !=
ipcMain.on('pinButton', () => {
    if (win.isAlwaysOnTop()) {
        win.setAlwaysOnTop(false);
    } else {
        win.setAlwaysOnTop(true);
    }
    win.webContents.send('pin', win.isAlwaysOnTop());
})

app.on('ready', () => {
    createWindow();
    tray = new Tray(trayIcon);
    tray.setTitle('Zar');
    tray.setToolTip('Zar Notepad');
    tray.on('click', () => win.show());
    var contextMenu = Menu.buildFromTemplate([
        {
            label: 'Zar Editor', enabled: false
        },
        {
            type: "separator"
        },
        {
            label: 'Show App', click: () => {
                win.show();
            }
        },
        {
            label: 'Minimize', click: () => {
                win.hide();
            }
        },
        {
            label: 'Quit', role: 'quit'
        }
    ])

    tray.setContextMenu(contextMenu);
    
});
