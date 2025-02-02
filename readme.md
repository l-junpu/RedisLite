# Redis Lite

Redis Lite is a lightweight, custom implementation of a key-value store that supports basic Redis-like functionality. It provides a simple TCP server and client application to handle multiple client connections and supports core operations such as `SET`, `GET`, and `DEL`. Additionally, Redis Lite allows you to set an expiration timer for keys when using the `SET` command.

## Features

- **Multiple Client Connections**: Redis Lite supports multiple clients connecting simultaneously via a TCP server.
- **Core Commands**:
  - `SET`: Store a key-value pair with an optional expiration time (in seconds).
  - `GET`: Retrieve the value associated with a given key.
  - `DEL`: Delete a key-value pair from the store.
- **Redis Serialization Protocol (RESP)**: Communication between the server and client applications follows the Redis Serialization Protocol (RESP).
- **Key Expiration**: You can set an expiration timer for keys when using the `SET` command, allowing automatic deletion of keys after a specified duration.
- **Help Command**: Use the `/help` command to display all available commands and their formats.

## Getting Started

### Prerequisites

- **C++17 Compiler**: Ensure you have a C++17 compatible compiler installed (e.g. MSVC).

### Installation

1. **Clone the Repository**:

   First, download the project files by cloning the repository. Open your terminal or command prompt and run:

   ```bash
   git clone https://github.com/l-junpu/RedisLite.git
   cd RedisLite
   ```

2. **Build the Project**:

   After downloading the project, you need to build it manually using `MSVC`.

3. **Run the Executables**:

   After building the project, you will have two executables: `RedisServer.exe` and `RedisClient.exe`.

   - Start the server:

     ```bash
     ./RedisServer
     ```

     By default, the server listens on `localhost` at port `27015`. You can modify the host and port in the source code if needed.

   - Start the client:

     ```bash
     ./RedisClient
     ```

     Once connected, you can issue commands like `SET`, `GET`, and `DEL` following the RESP protocol.

### Example Usage

#### SET Command

Set a key-value pair with an optional expiration time (in milliseconds):

```bash
SET mykey "Hello, Redis Lite!" 10000
```

This will store the key `mykey` with the value `"Hello, Redis Lite!"` and set it to expire after 10 milliseconds.

#### GET Command

Retrieve the value associated with a key:

```bash
GET mykey
```

If the key exists and has not expired, the server will return the value. Otherwise, it will return `nil`.

#### DEL Command

Delete a key-value pair:

```bash
DEL mykey
```

This will remove the key `mykey` from the store.

#### HELP Command

To display all available commands and their formats, use the `/help` command:

```bash
/help
```

This will output a list of supported commands along with their usage examples.

## The End

Feel free to reach out if you have any questions or need further assistance!

Happy using Redis Lite! 🚀