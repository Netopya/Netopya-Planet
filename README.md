# Netopya Planet Blog

This is the migrated version of the Netopya Planet blog, converted from PHP to a static site using [Eleventy](https://www.11ty.dev/).

## Migration Summary

The blog has been successfully migrated from a PHP-based dynamic site to a static site generator. The migration includes:

- **14 articles** converted from the original database (2013-2017)
- **Category pages** for Tutorials, Projects, and Tools
- **Responsive design** using Bootstrap 5 framework
- **Static assets** organized in the src directory following Eleventy best practices
- **Image galleries** with carousels for posts that have associated photos
- **Bootstrap 5** managed as npm dependency for better maintainability
- **Zero jQuery dependency** - Pure vanilla JavaScript with Bootstrap 5

## Gallery Features

Several posts include interactive image carousels with project photos:

### Posts with Galleries:
- **DIY Charging Station** (2013) - 18 images showing the woodworking process
- **The AEMD Alpha** (2013) - 6 images of Arduino project assembly
- **Controlling Multiple I2C Devices** (2014) - 5 images of circuit setup
- **Raspberry Pi LCD Screen** (2014) - 9 images of recycling project
- **OPUS en ligne Review** (2015) - 18 images of the device unboxing and setup

Each gallery includes:
- **Full-screen carousel** with navigation controls
- **Thumbnail grid** for quick navigation
- **Image descriptions** with context about each photo
- **Responsive design** that works on all devices
- **Modern vanilla JavaScript** - No jQuery dependency

## Project Structure

```
src/
├── _layouts/           # Page layouts
│   ├── base.njk       # Base layout with header/footer
│   └── post.njk       # Article layout with gallery support
├── _includes/         # Reusable components
│   ├── navbar.njk     # Navigation bar
│   └── footer.njk     # Site footer
│   └── image-carousel.njk  # Gallery carousel component
├── _data/             # Global data and gallery images
│   ├── galleries.json # Master gallery index
│   ├── gallery_*.json # Individual gallery data files
│   └── eleventyComputed.js # Dynamic data loading
├── posts/             # Blog posts (Markdown)
├── assets/            # All static assets
│   ├── images/        # Organized image assets
│   │   ├── article_images/  # Article-specific images
│   │   ├── gallery_images/  # Gallery images with thumbnails
│   │   └── site/           # General site images
│   ├── css/           # Stylesheets (from original site)
│   └── js/            # JavaScript files (jQuery-free)
├── index.njk          # Homepage
├── tutorials.njk      # Tutorials category page
├── projects.njk       # Projects category page
├── tools.njk          # Tools category page
└── about.njk          # About page
```

## Features

- **Static site generation** with Eleventy
- **Responsive design** using Bootstrap 5
- **Modern npm-based dependency management** - Bootstrap 5 included as dependency
- **jQuery-free implementation** - Pure vanilla JavaScript and Bootstrap 5 components
- **Category-based organization** (Tutorials, Projects, Tools)
- **Article excerpts** on listing pages
- **Date formatting** and metadata
- **OpenGraph meta tags** for social sharing
- **Clean URLs** with proper permalinks
- **Self-contained assets** - all images and assets organized in src/
- **Modern Bootstrap 5 components** - Updated navigation, breadcrumbs, badges, and carousel

## Development

### Prerequisites

- Node.js (v14 or higher)
- npm

### Installation

```bash
npm install
```

### Development Server

```bash
npm run serve
# or
npm start
```

The site will be available at `http://localhost:8080`

### Build for Production

```bash
npm run build
```

The built site will be in the `_site` directory.

## Technology Stack

- **Eleventy** - Static site generator
- **Nunjucks** - Template engine
- **Bootstrap 5** - CSS framework (managed via npm)
- **Vanilla JavaScript** - Modern ES6+ without jQuery dependency
- **Node.js** - Build tooling

## Upgrade Notes

The site has been upgraded from Bootstrap 3 to Bootstrap 5, with the following improvements:
- Better responsive breakpoints and utilities
- Modern component structure (navbar, breadcrumbs, badges)
- Improved carousel with better accessibility
- npm-based dependency management instead of static assets
- **Complete jQuery removal** - All functionality converted to vanilla JavaScript
- Modern JavaScript with Bootstrap 5's native API
- Reduced bundle size and improved performance

## Original Content

The original PHP blog content has been preserved in the `old/` directory for reference:
- `old/netopyaplanet/` - Original PHP source code
- `old/netopyadb.sql` - Database export with articles

All assets have been migrated to `src/assets/` for better organization and maintainability.

## Articles Migrated (14 total)

### 2013
1. **Hello World!** - Project introduction
2. **DIY Charging Station** - Tutorial on building a custom charging station  
3. **The AEMD Alpha** - Arduino Entertainment Multimedia Device project
4. **Introducing Bytety** - Tool for LED matrix graphics

### 2014  
5. **LED Matrices with Arduino, Netopya's Way** - Tutorial on Arduino LED programming
6. **Controlling Multiple I2C Devices with Arduino** - Tutorial on I2C multiplexers
7. **Introducing IP Planner!** - League of Legends influence points calculator
8. **Audio Virtual Reality** - Head-tracking audio project
9. **Recycling a Laptop LCD Screen into a Raspberry Pi Test Bench** - Hardware tutorial

### 2015
10. **OPUS en ligne Review** - Review of Quebec transit card reader
11. **$4 Computer Backlighting System** - DIY ambient lighting project

### 2016-2017
12. **Show images with an Arduino on a RGB LED Matrix** - LED matrix display system
13. **Improving JavaScript Code Quality** - SonarQube code analysis tutorial
14. **Introducing Chrome Memory Checker** - Chrome RAM usage monitoring tool

## Content Categories

- **6 Tutorials** - Step-by-step guides and educational content
- **5 Projects** - Hardware and software project showcases  
- **3 Tools** - Utility applications and software tools

## Next Steps

- Optimize images and static assets
- Add RSS feed generation
- Implement search functionality
- Add more styling/themes
- Deploy to a static hosting service (Netlify, Vercel, etc.)
- Consider adding dark mode support with Bootstrap 5's built-in utilities