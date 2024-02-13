# 📋 UART JSON Parser: 
This repository contains the codebase for implementing requirements and functionalities for the project. 

🔎 **Requirements:**
- **NFR1:** The system will be developed based on Erika OS.
- **NFR2:** Use existing functions of the system as far as sensible and possible.
- **NFR3:** We will use the library [jsmn](https://github.com/zserge/jsmn) for JSON parsing.
- **NFR4:** Put the developed code in sensible files and functions. Avoid global data unless absolutely required! A good choice would be to create `parser.c|.h` and `drawer.c|.h`.
- **NFR5:** You will find a couple of header files with the complete data types and API definitions in Moodle. Use these files without modification and add implementation files as needed.

🚀 **Functional Requirements:**
- **FR1:** The UART ISR will receive the incoming data and after checking the correct reception will store the byte in a global dynamic message buffer.
- **FR2:** In case of a reception error, a sensible error handling needs to be implemented, e.g. discard all bytes of the current JSON string and resynchronize with the next transfer. Of course, an error message shall be provided to the user.
- **FR3:** The receiving task will parse the JSON string and send the content to a low-priority output task, using messaging.
- **FR4:** Parsing errors must be detected and handled.
- **FR5:** The output task will use the TFT display to draw the content of the JSON protocol system.

🛠️ **Development Guidelines:**
- Follow the provided API definitions and data types.
- Implement functionalities as modular files and functions.
- Ensure error handling and robustness in code implementation.

📝 **Contributing:**
- Fork the repository.
- Make changes in feature branches.
- Submit pull requests for review.

📌 **Version Control:**
- Use meaningful commit messages.
- Keep commits focused and atomic.

🔧 **Setup:**
- Refer to the provided documentation for setup instructions and dependencies.

📬 **Communication:**
- Use GitHub issues for bug reports and feature requests.
- Join the discussions on the relevant channels.

🌟 **Acknowledgments:**
- Special thanks to contributors and supporters.
