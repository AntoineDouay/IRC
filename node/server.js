const net = require('net');
const axios = require('axios');

const server = net.createServer((socket) => {
  console.log('Client connected');

  // Handle incoming data
  socket.on('data', async (data) => {
    const receivedData = data.toString();
    console.log('Received data:', receivedData);
	const token = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpZCI6Ijh4aTBLT001XzU0Vk9OT2hmTFMxRCIsIm5jIjoiVk1LSWFhU2kyWjg2OUd1WWpZOVU2IiwiaWF0IjoxNjk4ODQ3MzU2LCJleHAiOjE3MDE0MzkzNTZ9.u94C3gR3dQcs8Nt1h1b1mMe2BJgxOAP4wp7eAnYVuTk"
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
