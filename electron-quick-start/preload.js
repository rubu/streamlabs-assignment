var ipc = require('electron').ipcRenderer

// All of the Node.js APIs are available in the preload process.
// It has the same sandbox as a Chrome extension.
window.addEventListener('DOMContentLoaded', () => {
    const replaceText = (selector, text) => {
        const element = document.getElementById(selector)
        if (element) element.innerText = text
    }

    for (const type of ['chrome', 'node', 'electron']) {
        replaceText(`${type}-version`, process.versions[type])
    }

    document.getElementById('start-streaming').addEventListener('click', function () {
        ipc.send('startStreaming', {
            twitchStreamKey: document.getElementById('twitch-stream-key').value
        })
    })

    // ipc hooks
    ipc.on('obsVersionString', function (event, response) {
        document.getElementById('obs-version').textContent = response
    })
    ipc.send('getObsVersionString')
    ipc.send('getVideoSources')
    ipc.send('getAudioSources')

})
