const net = require('net');
const axios = require('axios');

const server = net.createServer((socket) => {
  console.log('Client connected');

  // Handle incoming data
  socket.on('data', async (data) => {
    const receivedData = data.toString();
    console.log('Received data:', receivedData);
	const token = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpZCI6IlhRcWdMaWlCaUhEVkxGTk9BeXl6MiIsIm5jIjoiZ1lSRExMNEx0amZoSExWNmRzNjRtIiwiaWF0IjoxNjk4MDk4MDQyLCJleHAiOjE3MDA2OTAwNDJ9.-wRNCjpwlqbFlOvUEKOCehO2YEMb9sE1tgYSzfE-pWI"
    const res = await axios.post("https://api.novelai.net/ai/generate", {
        "input": receivedData,
        "model": "euterpe-v2",
        "parameters": {
            "use_string": true,
            "temperature": 1,
            "min_length": 10,
            "max_length": 30
        }
    }, {
        headers: {
            Authorization: `Bearer ${token}`
        }
    });
    // Send the response back to the client
    socket.write(res.data.output);
  });

  // Handle client disconnect
  socket.on('end', () => {
    console.log('Client disconnected');
  });
});

const PORT = 4000;
server.listen(PORT, () => {
  console.log(`Server listening on port ${PORT}`);
});
